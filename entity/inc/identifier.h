#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "common_lib.h"

class Identifier
{
public:
    Identifier(string name);
    virtual ~Identifier();
    virtual string getName() = 0;

protected:
    string name;
};

#endif