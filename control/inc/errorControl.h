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

    void printToConsole(QString message);
    void printErrorMsg(ResultState result);
    void printErrorMsg(QString errorMsg);
    void printErrorMsgAtLine(ResultState result, qint16 lineNum);

private:
    QString convertErrorMsg(ResultState result);
    OutputTabWidget* consoleTab;
    OutputTabWidget* errorTab;
};
#endif // ERRORCONTROL_H
