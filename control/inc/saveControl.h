#ifndef SAVE_CTL_H
#define SAVE_CTL_H

#include "../../entity/inc/common_lib.h"
#include "../../interface/inc/outputtabwidget.h"
#include "../../entity/inc/program.h"

class SaveControl
{

public:
    SaveControl(QString programPath, OutputTabWidget* consoleTab, OutputTabWidget* errorTab);
    ~SaveControl();
    Program* save();
    Program* loadFromJSON();

private:
    QString pgmPath;
    OutputTabWidget* consoleTab;
    OutputTabWidget* errorTab;
};

#endif
