#ifndef COMPILE_CTL_H
#define COMPILE_CTL_H

#include "../../entity/inc/common_lib.h"
#include "../../entity/inc/program.h"

class CompileControl
{
public:
    CompileControl(Program*);
    ~CompileControl();
    ResultState compile();

private:
    Program* program;
};

#endif
