#include "../inc/runControl.h"

RunControl::RunControl(Program* program)
{
    this->program = program;
}

RunControl::~RunControl()
{
}

ResultState RunControl::run()
{
    ResultState res = program->run();
    return res;
}
