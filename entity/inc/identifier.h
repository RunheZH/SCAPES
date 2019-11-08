#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <QJsonObject>
#include "common_lib.h"

class Identifier
{
public:
    explicit Identifier(QString aName, TypeE aType): name(aName), type(aType){}
    QString getName() const {return name;}
    TypeE getType() const {return type;}
    virtual QJsonObject toJSon() = 0;
    virtual ~Identifier() = default;

protected:
    QString name;
    TypeE type;
};

#endif
