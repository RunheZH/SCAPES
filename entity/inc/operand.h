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
    void setIsStr(bool boolean);
    int getValue();
    QString getPValue();
    int getIndex();
    bool getIsLiteral();
    bool getIsStr();

private:
    Identifier* id;
    bool isStr;
    int value;
    int index;
    bool isLiteral;
    QString pValue;
};

#endif
