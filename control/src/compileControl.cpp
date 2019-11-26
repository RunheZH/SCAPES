#include "../inc/compileControl.h"

CompileControl::CompileControl(Program* program)
{
    this->program = program;
}

CompileControl::~CompileControl()
{
}

ResultState CompileControl::compile()
{
    return program->compile();
}
