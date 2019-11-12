#include "../inc/compStmt.h"

CompStmt::CompStmt(QString pgmName, QString stmt, Label* lbl, qint16 lnNum) : Statement(pgmName, stmt, lbl, lnNum)
{
    qDebug() << "CompStmt()";
}

CompStmt::~CompStmt()
{
    delete (op1);
    delete (op2);
    qDebug() << "~CompStmt()";
}

ResultState CompStmt::compile()
{
    qDebug() << "CompStmt.compile()";
    QStringList args = this->statement.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if (args.size() != 3){
        if(args.size() == 1){
            return NO_OPERAND_ONE_ERROR;
        }
        if(args.size() == 2){
            return NO_OPERAND_TWO_ERROR;
        }
        else {
            return OPERAND_NUMBER_EXCEED_ERROR;
        }
    }

    QString instruction = args[0];
    QString operand1 = args[1];
    QString operand2 = args[2];

    JsonHandler jsonHdlr(this->programName);
    // TODO: not necessary to be ints
    op1 = new Operand(jsonHdlr.findVariable(operand1));
    op2 = new Operand(jsonHdlr.findVariable(operand2));

    // Variable 1 found
    if (op1->getIdentifier() != nullptr){
        // Variable 2 NOT found
        if (op2->getIdentifier() == nullptr){
            return VARIABLE_TWO_NOT_FOUND_ERROR;
        }
    }
    // Variable 1 NOT found
    else{
        // Variable 2 found
        if (op2->getIdentifier() != nullptr){
            return VARIABLE_ONE_NOT_FOUND_ERROR;
        }
        // Variable 2 NOT found
        else {
            return VARIABLE_ONE_AND_TWO_NOT_FOUND_ERROR;
        }
    }

    QJsonObject op1Obj = jsonHdlr.getJsonObj(OP_1, operand1);
    QJsonObject op2Obj = jsonHdlr.getJsonObj(OP_2, operand2);
    QJsonObject stmtObj = jsonHdlr.getJsonObj(instruction, jsonHdlr.appendToEnd(op1Obj, op2Obj));
    jsonHdlr.addElement(STMT, QString::number(lineNum), stmtObj);

    if (label)
    {
        jsonHdlr.addElement(LABEL, label->getName(), label->toJSON());
    }

    return NO_ERROR;
}

ResultState CompStmt::run()
{
    qDebug() << "CompStmt.run()";
    return NO_ERROR;
}
