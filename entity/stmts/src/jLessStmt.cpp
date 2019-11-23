#include "../inc/jLessStmt.h"

JLessStmt::JLessStmt(QString pgmName, QString stmt, Label* lbl, qint16 lnNum) : Statement(pgmName, stmt, lbl, lnNum)
{
    qDebug() << "JLessStmt()";
}

JLessStmt::~JLessStmt()
{
    delete (op1);
    qDebug() << "~JLessStmt()";
}

ResultState JLessStmt::compile()
{
    qDebug() << "JLessStmt.compile()";
    QStringList args = this->statement.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if (args.size() != 2){
        if(args.size() == 1){
            return NO_OPERAND_ONE_ERROR;
        }
        else {
            return OPERAND_NUMBER_EXCEED_ERROR;
        }
    }

    JsonHandler jsonHdlr(this->programName);
    QString instruction = args[0];
    QString operand1 = args[1];

    this->op1 = new Operand(jsonHdlr.findLabel(operand1));

    // Label 1 not found
    if(this->op1->getIdentifier() == nullptr){
        return LABEL_NOT_FOUND_ERROR;
    }

    QJsonObject op1Obj = JsonHandler::getJsonObj(OP_1, operand1);
    QJsonObject stmtObj = JsonHandler::getJsonObj(instruction, op1Obj);
    jsonHdlr.addElement(STMT, QString::number(lineNum), stmtObj);

    if (label)
    {
        jsonHdlr.addElement(LABEL, label->getName(), label->toJSON());
    }

    return NO_ERROR;
}

ResultState JLessStmt::run()
{
    qDebug() << "JLessStmt.run()";
    return NO_ERROR;
}
