#ifndef SAVE_CTL_H
#define SAVE_CTL_H

#include "../../entity/inc/common_lib.h"
#include "../../entity/inc/program.h"

class SaveControl
{
public:
    SaveControl(QString programPath);
    ~SaveControl();
    Program* save();

private:
    QString pgmName;
    QString pgmPath;
};

#endif
