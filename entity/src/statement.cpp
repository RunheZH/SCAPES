#include "../inc/statement.h"

Statement::Statement(QString programName, QString statement, QMap<QString, std::shared_ptr<Identifier>>& ids, int lineNum) : ids(ids)
{
    this->programName = programName;
    this->statement = statement;
    //this->ids = ids;
    this->lineNum = lineNum;
    this->label = nullptr;
    QStringList args = statement.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if (args[0].endsWith(":")){
        // detect a label
        this->label = new Label(this->programName, args[0].left(args[0].lastIndexOf(":")), lineNum);
        ids.insert(this->label->getName(), std::shared_ptr<Label>(this->label));
        JsonHandler jsonHdlr(this->programName);
        jsonHdlr.addElement(LABEL, label->getName(), label->toJSON());
        // get rid of the leading spaces
        this->statement = statement.mid(args[0].length() + 1);
    }
}

Statement::~Statement(){}

ResultState Statement::checkVariable(QString& operand, Operand& op, bool checkLiteral)
{
    QRegExp num_pattern("^\\-?\\d+\\.?\\d*$");
    QRegExp int_pattern("^\\-?\\d+$");
    QRegExp array_pattern("\\[\\w+\\]");
    if (operand.contains(num_pattern) && checkLiteral) // it's a literal
    {
        if (operand.contains(int_pattern)){
            // save the value to print out in Operand class only
            // b/c it is not a variable, nor an element of an array
            op.setValue(operand.toInt());
            op.setIsLiteral(true);
        }
        else
            return NOT_INTEGER_ERROR;
    }
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

            QString posStr = op_args[1];
            bool isInt = false;
            int posInt = posStr.toInt(&isInt);
            if (!isInt)
                posInt = 0;
            if (posInt < 0) {
                return INVALID_OPERAND;
            }
            // make sure the user won't skip initializing an element in this array (e.g. rdi arr[0], rdi arr[1], rdi arr[3])
            if (posInt >= dynamic_cast<Variable*>(foundVar_it.value().get())->getUsedSize())
                return VARIABLE_NOT_INIT_ERROR;

            op.setIdentifier(foundVar_it.value().get());
            op.setIndex(posInt);
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

ResultState Statement::getResultStateForTwoOp(ResultState resultState1, ResultState resultState2)
{
    // return a ResultState based on different scenarios
    switch (resultState1) {
    case NO_ERROR:
        switch (resultState2) {
        case NOT_INTEGER_ERROR:
            return NOT_INTEGER_ERROR;
        case INDEX_OUT_OF_BOUNDS:
            return INDEX_OUT_OF_BOUNDS;
        case DIFF_TYPE_ERROR:
            return DIFF_TYPE_ERROR;
        case EXPECT_INT_OR_ARR_ELM_ERROR:
            return EXPECT_INT_OR_ARR_ELM_ERROR;
        case VARIABLE_NOT_INIT_ERROR:
            return VARIABLE_TWO_NOT_INIT_ERROR;
        case VARIABLE_NOT_FOUND_ERROR:
            return VARIABLE_TWO_NOT_FOUND_ERROR;
        default:
            return NO_ERROR;
        }
    case NOT_INTEGER_ERROR:
        return NOT_INTEGER_ERROR;
    case INDEX_OUT_OF_BOUNDS:
        return INDEX_OUT_OF_BOUNDS;
    case DIFF_TYPE_ERROR:
        return DIFF_TYPE_ERROR;
    case VARIABLE_NOT_INIT_ERROR:
        switch (resultState2) {
        case VARIABLE_NOT_INIT_ERROR:
            return VARIABLE_ONE_AND_TWO_NOT_INIT_ERROR;
        case VARIABLE_NOT_FOUND_ERROR:
            return VARIABLE_ONE_NOT_INIT_AND_TWO_NOT_FOUND_ERROR;
        default:
            return VARIABLE_ONE_NOT_INIT_ERROR;
        }
    case VARIABLE_NOT_FOUND_ERROR:
        switch (resultState2) {
        case VARIABLE_NOT_INIT_ERROR:
            return VARIABLE_ONE_NOT_FOUND_AND_TWO_NOT_INIT_ERROR;
        case VARIABLE_NOT_FOUND_ERROR:
            return VARIABLE_ONE_AND_TWO_NOT_FOUND_ERROR;
        default:
            return VARIABLE_ONE_NOT_FOUND_ERROR;
        }
    default:
        return NO_ERROR;
    }
}
