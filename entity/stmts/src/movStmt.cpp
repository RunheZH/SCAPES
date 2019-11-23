#include "../inc/movStmt.h"

MovStmt::MovStmt(QString pgmName, QString stmt, Label* lbl, qint16 lnNum) : Statement(pgmName, stmt, lbl, lnNum)
{
    qDebug() << "MovStmt()";
}

MovStmt::~MovStmt()
{
    delete (op1);
    delete (op2);
    qDebug() << "~MovStmt()";
}

ResultState MovStmt::compile()
{
    qDebug() << "MovStmt.compile()";

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
    ResultState finalResultSate = checkTwoOperand(operand1, op1, operand2, op2);
    if (finalResultSate != NO_ERROR) {
        return finalResultSate;
    }

    QJsonObject op1Obj = JsonHandler::getJsonObj(OP_1, operand1);
    QJsonObject op2Obj = JsonHandler::getJsonObj(OP_2, operand2);
    QJsonObject stmtObj =JsonHandler::getJsonObj(instruction, JsonHandler::appendToEnd(op1Obj, op2Obj));
    jsonHdlr.addElement(STMT, QString::number(lineNum), stmtObj);

    if (label)
    {
        jsonHdlr.addElement(LABEL, label->getName(), label->toJSON());
    }

    return NO_ERROR;
}

ResultState MovStmt::run()
{
    qDebug() << "MovStmt.run()";
    return NO_ERROR;
}
