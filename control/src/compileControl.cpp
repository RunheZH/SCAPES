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
    qDebug() << "Hello World";
    ResultState res = program->compile();
    return res;
}
