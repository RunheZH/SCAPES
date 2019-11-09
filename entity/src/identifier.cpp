#include "../inc/identifier.h"

Identifier::Identifier(QString name)
{
    this->name = name;
}

Identifier::~Identifier(){}

QString Identifier::getName()
{
    return this->name;
}
