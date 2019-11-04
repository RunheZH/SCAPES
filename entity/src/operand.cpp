#include "../inc/operand.h"

Operand::Operand(QString value)
{
    this->value = value;
}

Operand::~Operand()
{
}

QString Operand::getValue()
{
    return this->value;
}

ResultState Operand::setValue(QString value)
{
    this->value = value;
}
