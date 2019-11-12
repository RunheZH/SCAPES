#include "../inc/printStmt.h"

PrintStmt::PrintStmt(QString pgmName, QString stmt, Label* lbl, qint16 lnNum) : Statement(pgmName, stmt, lbl, lnNum)
{
    qDebug() << "PrintStmt()";
}

PrintStmt::~PrintStmt()
{
    qDebug() << "~PrintStmt()";
}

ResultState PrintStmt::compile()
{
    qDebug() << "PrintStmt.compile()";

    QStringList args_str = this->statement.split(QRegExp("\\s*\"\\s*"), QString::SkipEmptyParts);

    //if (args_str.size() == 2) {}

    QStringList args = this->statement.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if (args.size() != 2){
        if(args.size() == 1){
            return NO_OPERAND_ONE_ERROR;
        }
        else {
            return OPERAND_NUMBER_EXCEED_ERROR;
        }
    }

    QString instruction = args[0];
    QString operand1 = args[1];

    JsonHandler jsonHdlr(this->programName);
    this->op1 = new Operand(jsonHdlr.findVariable(operand1));

    // Variable 1 not found
    if(this->op1->getIdentifier() == nullptr){
        return VARIABLE_ONE_NOT_FOUND_ERROR;
    }

    QJsonObject op1Obj = jsonHdlr.getJsonObj(OP_1, operand1);
    QJsonObject stmtObj = jsonHdlr.getJsonObj(instruction, op1Obj);
    jsonHdlr.addElement(STMT, QString::number(lineNum), stmtObj);

    if (label)
    {
        jsonHdlr.addElement(LABEL, label->getName(), label->toJSON());
    }

    return NO_ERROR;
}

ResultState PrintStmt::run()
{
    qDebug() << "PrintStmt.run()";
    return NO_ERROR;
}
