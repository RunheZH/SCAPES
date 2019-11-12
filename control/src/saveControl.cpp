#include "../inc/saveControl.h"

SaveControl::SaveControl(QString pgmPath, OutputTabWidget* consoleTab, OutputTabWidget* errorTab)
{
    this->pgmPath = pgmPath;
    this->consoleTab = consoleTab;
    this->errorTab = errorTab;
}

SaveControl::~SaveControl()
{
}

Program* SaveControl::save()
{
    Program* pgm = new Program(pgmPath, consoleTab, errorTab);
    pgm->save();
    return pgm;
}
