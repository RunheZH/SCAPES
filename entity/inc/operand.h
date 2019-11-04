#ifndef OPERAND_H
#define OPERAND_H

#include "common_lib.h"
#include "identifier.h"

class Operand
{
public:
    Operand(QString value);
    ~Operand();
    QString getValue();
    ResultState setValue(QString value);

private:
    QString value; // use string for now, change it later
    Identifier* id;
};

#endif
