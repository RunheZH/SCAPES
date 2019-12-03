#include "../inc/compStmt.h"

CompStmt::CompStmt(QString pgmName, QString stmt, QMap<QString, std::shared_ptr<Identifier>>& idsLib, int lnNum) : Statement(pgmName, stmt, idsLib, lnNum){}

CompStmt::~CompStmt()
{
    delete (op1.getIdentifier());
    delete (op2.getIdentifier());
}

ResultState CompStmt::compile()
{
    QStringList args = this->statement.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if (args.size() != 3){
        if(args.size() == 1){
            return NO_OPERAND_ONE_AND_TWO_ERROR;
        }
        else if(args.size() == 2){
            return NO_OPERAND_TWO_ERROR;
        }
        else {
            return OPERAND_NUMBER_EXCEED_ERROR;
        }
    }

    QString instruction = args[0];
    QString operand1 = args[1];
    QString operand2 = args[2];

    // syntax checking
    ResultState op1RS = checkVariable(operand1, op1, true); // set checkLiteral to true
    ResultState op2RS = checkVariable(operand2, op2, true); // set checkLiteral to true
    ResultState re = getResultStateForTwoOp(op1RS, op2RS);
    if (re != NO_ERROR)
        return re;

    JsonHandler jsonHdlr(this->programName);
    QJsonObject op1Obj = JsonHandler::getJsonObj(OP_1, operand1);
    QJsonObject op2Obj = JsonHandler::getJsonObj(OP_2, operand2);
    QJsonObject stmtObj =JsonHandler::getJsonObj(instruction, JsonHandler::appendToEnd(op1Obj, op2Obj));
    jsonHdlr.addElement(STMT, QString::number(lineNum), stmtObj);

    return NO_ERROR;
}

ReturnValue* CompStmt::run()
{
    qDebug() << "CompStmt.run()";

    Variable* variable1 = static_cast<Variable*>(op1.getIdentifier());
    Variable* variable2 = static_cast<Variable*>(op2.getIdentifier());
    //int result = variable1 - variable2;
                //variable 1 bigger: result>0
                //variable 2 bigger: result<0
                //var1=var2:         reuslt=0

    return new ReturnValue(NO_ERROR, NO_JUMP, 0);
}
