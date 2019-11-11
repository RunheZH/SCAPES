#ifndef VARIABLE_H
#define VARIABLE_H

#include "common_lib.h"
#include "identifier.h"
#include "../inc/jsonHandler.h"

class Variable : public Identifier
{
public:
    Variable(QString variableName, TypeE variableType);
    ~Variable();
    QJsonObject toJSON();
    void setValue(QString value, TypeE type);
    TypeE getType();

private:
    TypeE type;
    QString value; // use string for now, change it later
};

#endif
