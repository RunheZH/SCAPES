#include "../inc/variable.h"

Variable::Variable(QString name) : Identifier(name)
{
}

Variable::~Variable()
{
}

QString Variable::getName()
{
    return this->name;
}
