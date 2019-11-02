#ifndef LABEL_H
#define LABEL_H

#include "common_lib.h"
#include "identifier.h"

class Label : public Identifier
{
public:
    Label(string name);
    ~Label();
    string getName();
    // and other getters, setters

private:
    string name;
    TypeE type;
    string value; // use string for now, change it later
};

#endif