#ifndef ERRORCONTROL_H
#define ERRORCONTROL_H

#include "../../interface/inc/outputtabwidget.h"
#include "../../entity/inc/common_lib.h"

class MainWindow;

class ErrorControl
{
public:
    ErrorControl(OutputTabWidget* consoleTab, OutputTabWidget* errorTab);
    ~ErrorControl();

    void printToConsole(ResultState result);
    void printErrorMsg(ResultState result);
    void printErrorMsgAtLine(ResultState result, qint16 lineNum);

private:
    OutputTabWidget* consoleTab;
    OutputTabWidget* errorTab;
};
#endif // ERRORCONTROL_H
