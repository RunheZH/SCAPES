#include "../inc/addStmt.h"

AddStmt::AddStmt(QString pgmName, QString stmt, QMap<QString, std::shared_ptr<Identifier>>& idsLib, int lnNum) :
    Statement(pgmName, stmt, idsLib, lnNum){}

AddStmt::~AddStmt()
{
    delete (op1.getIdentifier());
    delete (op2.getIdentifier());
}

ResultState AddStmt::compile()
{
    QStringList args = this->statement.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if (args.size() != 3){ // syntax checking
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
    ResultState op2RS = checkVariable(operand2, op2, true);
    if (op2.getIsLiteral() || op2RS == NOT_INTEGER_ERROR)
        op2RS = EXPECT_INT_OR_ARR_ELM_ERROR;
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

ReturnValue* AddStmt::run()
{
    qDebug() << "AddStmt.run()";
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

    Variable* op2Var = dynamic_cast<Variable*>(op2.getIdentifier());
    TypeE op2Type = op2Var->getType();
    int op2Pos = 0;
    if(op2Type == INT)
        operand2 = op2Var->getValue(op2Pos);
    else // array element
    {
        operand2 = op2Var->getValue(op2.getIndex());
        op2Pos = op2.getIndex();
    }

    int newValue = operand1 + operand2;

    // replace operand2's value with new value
    dynamic_cast<Variable*>(op2.getIdentifier())->setValue(newValue, op2Pos);
    return new ReturnValue(NO_ERROR);
}
