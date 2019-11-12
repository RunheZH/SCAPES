#include "../inc/errorControl.h"

ErrorControl::ErrorControl(OutputTabWidget* consoleTab, OutputTabWidget* errorTab)
{
    this->consoleTab = consoleTab;
    this->errorTab = errorTab;
}

ErrorControl::~ErrorControl(){}

void ErrorControl::printToConsole(ResultState result)
{
    if (result == NO_ERROR)
        this->consoleTab->addText("no error");
}

void ErrorControl::printErrorMsg(ResultState result)
{
    if (result == NO_ERROR)
        this->errorTab->addText("no error");
}

void ErrorControl::printErrorMsgAtLine(ResultState result, qint16 lineNum)
{
    if (result == NO_ERROR)
        this->errorTab->addText("no error at line " + QString::number(lineNum));
}
