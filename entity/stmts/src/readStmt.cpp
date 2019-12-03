#include "../inc/readStmt.h"

ReadStmt::ReadStmt(QString pgmName, QString stmt, QMap<QString, std::shared_ptr<Identifier>>& idsLib, int lnNum) : Statement(pgmName, stmt, idsLib, lnNum){}

ReadStmt::~ReadStmt()
{
    delete (op1.getIdentifier());
}

ResultState ReadStmt::compile()
{
    qDebug() << "ReadStmt.compile()";
    QStringList args = this->statement.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if (args.size() != 2){ // syntax checking
        if(args.size() == 1){
            return NO_OPERAND_ONE_ERROR;
        }
        else {
            return OPERAND_NUMBER_EXCEED_ERROR;
        }
    }

    QString instruction = args[0];
    QString operand1 = args[1];

    ResultState re = checkVariable(operand1, op1, true);
    if (re != NO_ERROR)
        return re;

    // set "initialized?" to true in JSON
    JsonHandler jsonHdlr(this->programName);
    if (dynamic_cast<Variable*>(op1.getIdentifier())->getType() == INT)
        jsonHdlr.initIntValue(op1.getIdentifier()->getName());
    else // array
        jsonHdlr.initArrayValue(op1.getIdentifier()->getName(), op1.getIndex());

    // add to JSON
    QJsonObject op1Obj = JsonHandler::getJsonObj(OP_1, operand1);
    QJsonObject stmtObj = JsonHandler::getJsonObj(instruction, op1Obj);
    jsonHdlr.addElement(STMT, QString::number(lineNum), stmtObj);

    return NO_ERROR;
}

ReturnValue* ReadStmt::run()
{
    qDebug() << "ReadStmt.run()";

    // Variable aVariable = DBM.getVariable(op1->getIdentifier()->getName());
    // Value newValue = UI.popRead(); OR Value newValue = controller.readValue();
    // aVariable.setValue(newValue);
    // DBM.setVariable(aVariable.getName(), aVariable.getType(), newValue);


    Variable* aVariable = static_cast<Variable*>(op1.getIdentifier());
    TypeE variableType = aVariable->getType();

    int newValue = 0;
    // TODO: include UI
    //newValue = UI.popRead();

    // if we set value to a int
    if (variableType == TypeE::INT){
        aVariable->setValue(newValue, 0);
    }
    // if we set value to an array
    else if (variableType == TypeE::ARRAY){
        // for loop to set value to every vector?
        aVariable->setValue(newValue, 0);
    }
    else{
        qDebug() << "ERROR";
    }

    return new ReturnValue(NO_ERROR, NO_JUMP, NO_CMP);
}

ResultState ReadStmt::checkVariable(QString& operand, Operand& op, bool checkLiteral)
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
        QStringList op1_args = operand.split(QRegExp("[\\[\\]]"), QString::SkipEmptyParts);
        QMap<QString, std::shared_ptr<Identifier>>::iterator foundVar_it = ids.find(op1_args[0]);
        if (foundVar_it != ids.end() && dynamic_cast<Variable*>(foundVar_it.value().get())) // found variable
        {
            if (dynamic_cast<Variable*>(foundVar_it.value().get())->getType() != ARRAY)
                return DIFF_TYPE_ERROR;

            // NOTE: different from Statement::checkOperand(...)
            // make sure the user won't skip initializing an element in this array (e.g. rdi arr[0], rdi arr[1], rdi arr[3])
            if ((op1_args[1].toInt() > dynamic_cast<Variable*>(foundVar_it.value().get())->getUsedSize()) ||
                    // and won't go over the max size of the array
                    (op1_args[1].toInt() >= dynamic_cast<Variable*>(foundVar_it.value().get())->getSize()))
                return INDEX_OUT_OF_BOUNDS;

            op.setIdentifier(foundVar_it.value().get());
            op.setIndex(op1_args[1].toInt());
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
