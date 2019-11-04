#include "../inc/saveControl.h"

SaveControl::SaveControl(QString pgmName, QString pgmPath)
{
    this->pgmName = pgmName;
    this->pgmPath = pgmPath;

}

SaveControl::~SaveControl()
{
}

Program* SaveControl::save()
{
    Program* pgm = new Program(pgmName, pgmPath);
    pgm->save();
}
