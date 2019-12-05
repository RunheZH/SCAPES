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
    consoleTab->clearText();
    Program* pgm = new Program(pgmPath, consoleTab, errorTab);
    consoleTab->addText("Saved successfully.");
    return pgm;
}

Program* SaveControl::loadFromJSON()
{
    consoleTab->clearText();
    if (pgmPath.contains(".json"))
        pgmPath = pgmPath.split(".json")[0];
    Program* pgm = new Program(pgmPath, consoleTab, errorTab);
    pgm->loadFromJSON();
    consoleTab->addText("Loaded successfully.");
    return pgm;
}
