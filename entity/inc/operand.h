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
    void setIsLiteral(bool boolean);
    QString getValue();
    int getIndex();
    bool getIsLiteral();

private:
    Identifier* id;
    bool exist_value;
    bool exist_intdex;
    int value;
    int index;
    bool isLiteral;
    QString pValue;
};

#endif
