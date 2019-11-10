#include "../inc/saveControl.h"

SaveControl::SaveControl(QString pgmPath)
{
    this->pgmPath = pgmPath;
}

SaveControl::~SaveControl()
{
}

Program* SaveControl::save()
{
    Program* pgm = new Program(pgmPath);
    pgm->save();
    return pgm;
}
