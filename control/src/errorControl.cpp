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

void ErrorControl::printErrorMsg(ResultState result)
{
    this->errorTab->addText(convertErrorMsg(result));
}

void ErrorControl::printErrorMsgAtLine(ResultState result, qint16 lineNum)
{
    this->errorTab->addText(convertErrorMsg(result) + " at line " + QString::number(lineNum));
}

QString ErrorControl::convertErrorMsg(ResultState result)
{
    if (result == FILE_OPEN_ERROR)
        return "Could not open file";
    else if (result == INVALID_STATEMENT)
        return "Invalid statement";
    else if (result == NO_OPERAND_ONE_ERROR)
        return "Missing first operand";
    else if (result == NO_OPERAND_TWO_ERROR)
        return "Missing second operand";
    else if (result == OPERAND_NUMBER_EXCEED_ERROR)
        return "Too much arguments";
    else if (result == VARIABLE_ONE_NOT_FOUND_ERROR)
        return "Undefined operand 1";
    else if (result == VARIABLE_TWO_NOT_FOUND_ERROR)
        return "Undefined operand 2";
    else if (result == VARIABLE_ONE_AND_TWO_NOT_FOUND_ERROR)
        return "Undefined operand 1 and operand 2";
    else if (result == LABEL_NOT_FOUND_ERROR)
        return "Undefined label";
    else if (result == NO_END)
        return "Missing 'end' at the end of the program";
    return "No error";
}
