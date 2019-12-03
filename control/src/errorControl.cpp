#include "../inc/errorControl.h"

ErrorControl::ErrorControl(OutputTabWidget* consoleTab, OutputTabWidget* errorTab)
{
    this->consoleTab = consoleTab;
    this->errorTab = errorTab;
}

ErrorControl::~ErrorControl(){}

void ErrorControl::printToConsole(QString message)
{
    this->consoleTab->addText(message);
}

void ErrorControl::printErrorMsg(QString errorMsg)
{
    this->errorTab->addText(errorMsg);
}

void ErrorControl::printErrorMsg(ResultState result)
{
    this->errorTab->addText(convertErrorMsg(result));
}

void ErrorControl::printErrorMsgAtLine(ResultState result, int lineNum)
{
    this->errorTab->addText(convertErrorMsg(result) + " at line " + QString::number(lineNum));
}

QString ErrorControl::convertErrorMsg(ResultState result)
{
    switch (result)
    {
    case NOT_INTEGER_ERROR:
        return "Must be an integer";
    case DIFF_TYPE_ERROR:
        return "Different type of operand is provided";
    case FILE_OPEN_ERROR:
        return "Could not open file";
    case INDEX_OUT_OF_BOUNDS:
        return "Index out of bounds";
    case INVALID_STATEMENT:
        return "Invalid statement";
    case INVALID_OPERAND:
        return "Invalid operand";
    case NO_OPERAND_ONE_ERROR:
        return "Missing the first operand";
    case NO_OPERAND_TWO_ERROR:
        return "Missing the second operand";
    case NO_OPERAND_ONE_AND_TWO_ERROR:
        return "Missing the first and the second operands";
    case OPERAND_NUMBER_EXCEED_ERROR:
        return "Too many arguments have been given to this statement";
    case EXPECT_INT_OR_ARR_ELM_ERROR:
        return "Not given an int or an element of an array";
    case VARIABLE_NOT_FOUND_ERROR:
        return "Undefined variable";
    case VARIABLE_ONE_NOT_FOUND_ERROR:
        return "The first variable is undefined";
    case VARIABLE_TWO_NOT_FOUND_ERROR:
        return "The second variable is undefined";
    case VARIABLE_ONE_AND_TWO_NOT_FOUND_ERROR:
        return "Both variables are undefined";
    case VARIABLE_NOT_INIT_ERROR:
        return "Variable has not been initialized yet";
    case VARIABLE_ONE_NOT_INIT_ERROR:
        return "The first variable has not been initialized yet";
    case VARIABLE_TWO_NOT_INIT_ERROR:
        return "The second variable has not been initialized yet";
    case VARIABLE_ONE_AND_TWO_NOT_INIT_ERROR:
        return "Both variables have not been initialized yet";
    case VARIABLE_ONE_NOT_FOUND_AND_TWO_NOT_INIT_ERROR:
        return "Undefined first variable and uninitialized second variable";
    case VARIABLE_ONE_NOT_INIT_AND_TWO_NOT_FOUND_ERROR:
        return "Unintialized first variable and undefined second variable";
    case LABEL_NOT_FOUND_ERROR:
        return "Undefined label";
    case COMPILATION_ERROR:
        return "Compilation error";
    case RUNTIME_ERROR:
        return "Runtime error";
    case NO_END:
        return "Missing a 'end' statement to end the program";
    default:
        return "No error";
    }
}
