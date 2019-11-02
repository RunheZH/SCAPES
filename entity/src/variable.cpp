#include "../inc/variable.h"

Variable::Variable(string name) : Identifier(name)
{
}

Variable::~Variable()
{
}

string Variable::getName()
{
    return this->name;
}