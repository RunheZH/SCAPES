#include "../inc/operand.h"

Operand::Operand(Identifier* id)
{
    this->id = id;
}

Operand::~Operand()
{
    if (id)
        delete (id);
}

Identifier* Operand::getIdentifier()
{
    return this->id;
}

void Operand::setIdentifier(Identifier* newId)
{
    this->id = newId;
}
