#ifndef VARIABLE_H
#define VARIABLE_H

#include "common_lib.h"
#include "identifier.h"

class Variable : public Identifier
{
public:
    Variable(QString name);
    ~Variable();
    QString getName();
    // and other getters, setters

private:
    TypeE type;
    QString value; // use string for now, change it later
};

#endif
