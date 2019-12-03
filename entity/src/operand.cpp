#include "../inc/operand.h"
#include "../inc/label.h"
#include "../inc/variable.h"

Operand::Operand()
{
    isLiteral = false;
    exist_value = false;
    exist_intdex = false;
    value = 0;
    index = 0;
}

Operand::Operand(Identifier* id)
{
    this->id = id;
    exist_value = false;
    exist_intdex = false;
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
    exist_value = true;
}

void Operand::setValue(QString pValue)
{
    this->pValue = pValue;
}

void Operand::setIndex(int index)
{
    this->index = index;
    exist_intdex = true;
}

void Operand::setIsLiteral(bool boolean)
{
    isLiteral = boolean;
}

QString Operand::getValue()
{
    QString str;
    /*
    if (exist_value) {
        str = QString::number(value, 10);
    }else if (!exist_intdex && id != nullptr){
        if ( Variable * v = dynamic_cast<Variable*>(id)) {
           str = v->getValue();
        } else if (Label * l = dynamic_cast<Label*>(id)){
           str.setNum(l->getLineNum());
        }
    } else if (id != nullptr){
        if ( Variable * v = dynamic_cast<Variable*>(id)) {
           str = v->getValue(index);
        }
    } else if (!exist_intdex && id == nullptr){
        return pValue;
    }*/
    return str;
}

int Operand::getIndex()
{
    return this->index;
}

bool Operand::getIsLiteral()
{
    return isLiteral;
}
