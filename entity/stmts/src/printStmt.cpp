#include "../inc/printStmt.h"

PrintStmt::PrintStmt(QString pgmName, QString stmt, QMap<QString, std::shared_ptr<Identifier>>& idsLib, int lnNum) : Statement(pgmName, stmt, idsLib, lnNum){}

PrintStmt::~PrintStmt()
{
    delete (op1.getIdentifier());
}

ResultState PrintStmt::compile()
{
    qDebug() << "PrintStmt.compile()";

    JsonHandler jsonHdlr(this->programName);
    QString instruction;
    QString operand1;
    QRegExp str_pattern("\"*\"");
    if (statement.contains(str_pattern)) // print a string
    {
        QStringList args_str = this->statement.split(QRegExp("\\s*\"\\s*"), QString::SkipEmptyParts);

        if (args_str.size() != 2){ // syntax checking
            if(args_str.size() == 1){
                return NO_OPERAND_ONE_ERROR;
            }
            else {
                return OPERAND_NUMBER_EXCEED_ERROR;
            }
        }
        instruction = args_str[0];
        // save the value to print out in Operand class only
        // b/c it is not a variable, nor an element of an array
        op1.setValue(args_str[1]);
        op1.setIsLiteral(true);
    }
    else // print a literal, int, or an element of an array
    {
        QStringList args = this->statement.split(QRegExp("\\s+"), QString::SkipEmptyParts);

        if (args.size() != 2){ // syntax checking
            if(args.size() == 1){
                return NO_OPERAND_ONE_ERROR;
            }
            else {
                return OPERAND_NUMBER_EXCEED_ERROR;
            }
        }

        instruction = args[0];
        operand1 = args[1];
        QRegExp num_pattern("^\\-?\\d+\\.?\\d*$");
        QRegExp array_pattern("\\[[0-9]+\\]");
        if (operand1.contains(num_pattern)) // it's a literal
        {
            // save the value to print out in Operand class only
            // b/c it is not a variable, nor an element of an array
            op1.setValue(operand1);
            op1.setIsLiteral(true);
        }
        else if (operand1.contains(QRegExp("\\[\\-[0-9]+\\]"))) // accessing an array using a negative index are not allowed
            return INDEX_OUT_OF_BOUNDS;
        else if (operand1.contains(array_pattern)) // an array element
        {
            // found variable and index
            QStringList op1_args = operand1.split(QRegExp("[\\[\\]]"), QString::SkipEmptyParts);
            QMap<QString, std::shared_ptr<Identifier>>::iterator foundVar_it = ids.find(op1_args[0]);
            if (foundVar_it != ids.end() && dynamic_cast<Variable*>(foundVar_it.value().get())) // found variable
            {
                if (dynamic_cast<Variable*>(foundVar_it.value().get())->getType() != ARRAY)
                    return DIFF_TYPE_ERROR;

                // make sure the user won't skip initializing an element in this array (e.g. rdi arr[0], rdi arr[1], rdi arr[3])
                if (op1_args[1].toInt() >= dynamic_cast<Variable*>(foundVar_it.value().get())->getUsedSize())
                    return ResultState::VARIABLE_NOT_INIT_ERROR;

                op1.setIdentifier(foundVar_it.value().get());
                op1.setIndex(op1_args[1].toInt());
            }
            else
                return VARIABLE_NOT_FOUND_ERROR;
        }
        else // int
        {
            if (ids.find(operand1) == ids.end())
                return VARIABLE_NOT_FOUND_ERROR;

            if (dynamic_cast<Variable*>(ids.find(operand1).value().get())->getType() != INT)
                return DIFF_TYPE_ERROR;

            op1.setIdentifier(ids.find(operand1).value().get());
        }

        // add to JSON file
        QJsonObject op1Obj;
        op1Obj = JsonHandler::getJsonObj(OP_1, operand1);

        QJsonObject stmtObj = JsonHandler::getJsonObj(instruction, op1Obj);
        jsonHdlr.addElement(STMT, QString::number(lineNum), stmtObj);
    }

    return NO_ERROR;
}

ReturnValue* PrintStmt::run()
{
    qDebug() << "PrintStmt.run()";

    // Variable aVariable = DBM.getVariable(op1->getIdentifier()->getName());
    // OR
    // Variable* aVariable = static_cast<Variable*>(op1->getIdentifier());
    // QString printedValue = aVariable->getValue();
    // qDebug() << printedValue;

    Variable* aVariable = static_cast<Variable*>(op1.getIdentifier());
    if (aVariable->getValue().isEmpty())
        return new ReturnValue(VARIABLE_NOT_FOUND_ERROR);

    QVector<int> aVector = aVariable->getValue();

    // if we read value from the INT type
    if (aVector.size() == 1){
        qDebug() << "the value of this int is:";
        qDebug() << aVariable->getValue(aVector[0]);
    }
    // if we read value from the ARRAY type
    else if (aVector.size() > 1){
        qDebug() << "the value of this array is:";
        for (int i=0; i<aVector.size(); i++){
            qDebug() << aVariable->getValue(aVector[i]);
        }
    }
    else{
        qDebug() << "ERROR";
    }


    return new ReturnValue(NO_ERROR, NO_JUMP, NO_CMP);
}
