#include "../inc/operand.h"

Operand::Operand(Identifier* id)
{
    this->id = id;
}

Operand::~Operand()
{
}

Identifier* Operand::getIdentifier()
{
    return this->id;
}

void Operand::setIdentifier(Identifier* newId)
{
    this->id = newId;
}
