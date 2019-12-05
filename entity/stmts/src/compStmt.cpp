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
    int operand1;
    int operand2;
    if (op1.getIsLiteral())
        operand1 = op1.getValue();
    else
    {
        Variable* op1Var = dynamic_cast<Variable*>(op1.getIdentifier());
        TypeE op1Type = op1Var->getType();
        if (op1Type == INT)
            operand1 = op1Var->getValue(0);
        else // array element
            operand1 = op1Var->getValue(op1.getIndex());
    }
    if (op2.getIsLiteral())
        operand2 = op2.getValue();
    else
    {
        Variable* op2Var = dynamic_cast<Variable*>(op2.getIdentifier());
        TypeE op2Type = op2Var->getType();
        if (op2Type == INT)
            operand2 = op2Var->getValue(0);
        else // array element
            operand2 = op2Var->getValue(op2.getIndex());
    }
    int result = NO_CMP;
    if (operand1 < operand2)
        result = -1;
    else if (operand1 == operand2)
        result = 0;
    else
        result = 1;

    return new ReturnValue(NO_ERROR, NO_JUMP, result);
}
