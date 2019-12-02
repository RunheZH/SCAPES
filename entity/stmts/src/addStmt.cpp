#include "../inc/addStmt.h"

AddStmt::AddStmt(QString pgmName, QString stmt, QMap<QString, std::shared_ptr<Identifier>>& idsLib, int lnNum) : Statement(pgmName, stmt, idsLib, lnNum)
{
    qDebug() << "AddStmt()";
}

AddStmt::~AddStmt()
{
    delete (op1.getIdentifier());
    delete (op2.getIdentifier());
    qDebug() << "~AddStmt()";
}

ResultState AddStmt::compile()
{
    qDebug() << "AddStmt.compile()";
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

    return NO_ERROR;
}

ReturnValue* AddStmt::run()
{
    qDebug() << "AddStmt.run()";
    return new ReturnValue(NO_ERROR, NO_JUMP, NO_CMP);
}
