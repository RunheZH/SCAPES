#include "../inc/movStmt.h"

MovStmt::MovStmt(QString pgmName, QString stmt, QMap<QString, std::shared_ptr<Identifier>>& idsLib, int lnNum) : Statement(pgmName, stmt, idsLib, lnNum){}

MovStmt::~MovStmt()
{
    delete (op1.getIdentifier());
    delete (op2.getIdentifier());
}

ResultState MovStmt::compile()
{
    qDebug() << "MovStmt.compile()";

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
    ResultState op1RS = Statement::checkVariable(operand1, op1, true); // set checkLiteral to true
    ResultState op2RS = checkVariable(operand2, op2, true);
    if (op2.getIsLiteral() || op2RS == NOT_INTEGER_ERROR)
        op2RS = EXPECT_INT_OR_ARR_ELM_ERROR;
    ResultState re = getResultStateForTwoOp(op1RS, op2RS);
    if (re != NO_ERROR)
        return re;

    // add to JSON file
    JsonHandler jsonHdlr(this->programName);
    QJsonObject op1Obj = JsonHandler::getJsonObj(OP_1, operand1);
    QJsonObject op2Obj = JsonHandler::getJsonObj(OP_2, operand2);
    QJsonObject stmtObj =JsonHandler::getJsonObj(instruction, JsonHandler::appendToEnd(op1Obj, op2Obj));
    jsonHdlr.addElement(STMT, QString::number(lineNum), stmtObj);

    return NO_ERROR;
}

ReturnValue* MovStmt::run()
{
    qDebug() << "MovStmt.run()";
    int operand1;
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
    int op2Pos = 0; // int
    if(op2Type == ARRAY)
    {
        op2Pos = op2.getIndex();
    }

    // replace operand2's old value with operand1's value
    dynamic_cast<Variable*>(op2.getIdentifier())->setValue(operand1, op2Pos);
    return new ReturnValue(NO_ERROR);
}

ResultState MovStmt::checkVariable(QString& operand, Operand& op, bool checkLiteral)
{
    QRegExp num_pattern("^\\-?\\d+\\.?\\d*$");
    QRegExp array_pattern("\\[[0-9]+\\]");
    if (operand.contains(num_pattern) && checkLiteral) // it's a literal
        return EXPECT_INT_OR_ARR_ELM_ERROR;
    else if (operand.contains(QRegExp("\\[\\-[0-9]+\\]"))) // accessing an array using a negative index are not allowed
        return INDEX_OUT_OF_BOUNDS;
    else if (operand.contains(array_pattern)) // an array element
    {
        // found variable and index
        QStringList op_args = operand.split(QRegExp("[\\[\\]]"), QString::SkipEmptyParts);
        QMap<QString, std::shared_ptr<Identifier>>::iterator foundVar_it = ids.find(op_args[0]);
        if (foundVar_it != ids.end() && dynamic_cast<Variable*>(foundVar_it.value().get())) // found variable
        {
            if (dynamic_cast<Variable*>(foundVar_it.value().get())->getType() != ARRAY)
                return DIFF_TYPE_ERROR;

            // NOTE: different from Statement::checkOperand(...)
            // make sure the user won't skip initializing an element in this array (e.g. rdi arr[0], rdi arr[1], rdi arr[3])
            if ((op_args[1].toInt() > dynamic_cast<Variable*>(foundVar_it.value().get())->getUsedSize()) ||
                    // and won't go over the max size of the array
                    (op_args[1].toInt() >= dynamic_cast<Variable*>(foundVar_it.value().get())->getSize()))
                return INDEX_OUT_OF_BOUNDS;

            op.setIdentifier(foundVar_it.value().get());
            op.setIndex(op_args[1].toInt());
            dynamic_cast<Variable*>(op.getIdentifier())->setUsedSize(dynamic_cast<Variable*>(op.getIdentifier())->getUsedSize() + 1);
        }
        else
            return VARIABLE_NOT_FOUND_ERROR;
    }
    else // int
    {
        if (ids.find(operand) == ids.end())
            return VARIABLE_NOT_FOUND_ERROR;

        if (dynamic_cast<Variable*>(ids.find(operand).value().get())->getType() != INT)
            return DIFF_TYPE_ERROR;

        op.setIdentifier(ids.find(operand).value().get());
    }
    return NO_ERROR;
}
