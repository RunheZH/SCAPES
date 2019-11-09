#ifndef VARIABLE_H
#define VARIABLE_H

#include "common_lib.h"
#include "identifier.h"

class Variable : public Identifier
{
public:
    Variable(QString aName, TypeE aType):Identifier(aName), type(aType){}
    ~Variable() override=default;
    virtual QJsonObject toJSon() override;
    TypeE getType() const;

private:
    TypeE type;
    QString value; // use string for now, change it later
};

#endif
