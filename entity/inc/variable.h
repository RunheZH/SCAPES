#ifndef VARIABLE_H
#define VARIABLE_H

#include "common_lib.h"
#include "identifier.h"

class Variable : public Identifier
{
public:
    Variable(string name);
    ~Variable();
    string getName();
    // and other getters, setters

private:
    TypeE type;
    string value; // use string for now, change it later
};

#endif