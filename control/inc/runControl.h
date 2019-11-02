#ifndef RUN_CTL_H
#define RUN_CTL_H

#include "../../entity/inc/common_lib.h"

class RunControl
{
public:
    RunControl();
    ~RunControl();
    ResultState run(string pgmName, string pgmScript);

private:
    string pgmName;
    string pgmScript;
};

#endif
