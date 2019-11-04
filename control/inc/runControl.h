#ifndef RUN_CTL_H
#define RUN_CTL_H

#include "../../entity/inc/common_lib.h"
#include "../../entity/inc/program.h"

class RunControl
{
public:
    RunControl(Program*);
    ~RunControl();
    ResultState run();

private:
    Program* program;
};

#endif
