#ifndef SAVE_CTL_H
#define SAVE_CTL_H

#include "../../entity/inc/common_lib.h"

class SaveControl
{
public:
    SaveControl();
    ~SaveControl();
    ResultState save(string pgmName, string pgmScript);

private:
    string pgmName;
    string pgmScript;
};

#endif
