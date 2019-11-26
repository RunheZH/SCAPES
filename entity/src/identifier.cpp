#include "../inc/identifier.h"

Identifier::Identifier(QString programName, QString name)
{
    this->name = name;
    this->programName = programName;
}

Identifier::~Identifier(){}

QString Identifier::getName()
{
    return this->name;
}
