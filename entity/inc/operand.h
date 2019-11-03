#ifndef OPERAND_H
#define OPERAND_H

#include "common_lib.h"
#include "identifier.h"

class Operand
{
public:
    Operand(string value);
    ~Operand();
    string getValue();
    ResultState setValue(string value);

private:
    string value; // use string for now, change it later
    Identifier* id;
};

#endif