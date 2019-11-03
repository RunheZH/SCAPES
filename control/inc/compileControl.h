#ifndef COMPILE_CTL_H
#define COMPILE_CTL_H

#include "../../entity/inc/common_lib.h"

class CompileControl
{
public:
    CompileControl();
    ~CompileControl();
    ResultState compile(string pgmName, string pgmScript);

private:
    string pgmName;
    string pgmScript;
};

#endif
