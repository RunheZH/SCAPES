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
    ResultState oneResultState = checkOperand(operand1, op1);
    ResultState twoResultState = checkOperand(operand2, op2);
    ResultState finalResultSate = getResultStateForTwo(oneResultState, twoResultState);
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

ResultState CompStmt::run()
{
    qDebug() << "CompStmt.run()";
    return NO_ERROR;
}
