#include "../inc/operand.h"

Operand::Operand(string value)
{
    this->value = value;
}

Operand::~Operand()
{
}

string Operand::getValue()
{
    return this->value;
}

ResultState Operand::setValue(string value)
{
    this->value = value;
}