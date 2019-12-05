#include "../inc/operand.h"
#include "../inc/label.h"
#include "../inc/variable.h"

Operand::Operand()
{
    isLiteral = false;
    isStr = false;
    value = 0;
    index = 0;
}

Operand::Operand(Identifier* id)
{
    this->id = id;
    isStr = false;
    isLiteral = false;
    value = 0;
    index = 0;
}

Operand::~Operand()
{
    if (id)
        delete id;
}

Identifier* Operand::getIdentifier()
{
    return this->id;
}

void Operand::setIdentifier(Identifier* newId)
{
    this->id = newId;
}

void Operand::setValue(int value)
{
    this->value = value;
}

void Operand::setValue(QString pValue)
{
    this->pValue = pValue;
}

void Operand::setIndex(int index)
{
    this->index = index;
}

void Operand::setIsLiteral(bool boolean)
{
    isLiteral = boolean;
}

void Operand::setIsStr(bool boolean)
{
    isStr = boolean;
}

int Operand::getValue()
{
    return value;
}

QString Operand::getPValue()
{
    return pValue;
}

int Operand::getIndex()
{
    return this->index;
}

bool Operand::getIsLiteral()
{
    return isLiteral;
}

bool Operand::getIsStr()
{
    return isStr;
}
