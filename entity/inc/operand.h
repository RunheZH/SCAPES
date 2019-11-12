#ifndef OPERAND_H
#define OPERAND_H

#include "common_lib.h"
#include "identifier.h"

class Operand
{
public:
    Operand(Identifier* id);
    ~Operand();
    Identifier* getIdentifier();
    void setIdentifier(Identifier*);

private:
    Identifier* id;
};

#endif
