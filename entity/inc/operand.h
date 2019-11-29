#ifndef OPERAND_H
#define OPERAND_H

#include "common_lib.h"
#include "identifier.h"

class Operand
{
public:
    Operand();
    Operand(Identifier* id);
    ~Operand();
    Identifier* getIdentifier();
    void setIdentifier(Identifier*);
    void setValue(int value);
    void setValue(QString pValue);
    void setIndex(int index);
    QString getValue();

private:
    Identifier* id;
    bool exist_value;
    bool exist_intdex;
    int value;
    int index;
    QString pValue;
};

#endif
