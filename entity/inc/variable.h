#ifndef VARIABLE_H
#define VARIABLE_H

#include "common_lib.h"
#include "identifier.h"

class Variable : public Identifier
{
public:
    Variable(QString aName, TypeE aType):Identifier(aName, aType){}
    virtual QJsonObject toJSon() override;

    // and other getters, setters

private:
    QString value; // use string for now, change it later
};

#endif
