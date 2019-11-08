#ifndef LABEL_H
#define LABEL_H

#include "common_lib.h"
#include "identifier.h"

class Label : public Identifier
{
public:
    Label(QString aName, TypeE aType):Identifier(aName, aType){}
    virtual QJsonObject toJSon() override;
    // and other getters, setters

private:
    QString value; // use string for now, change it later
};

#endif
