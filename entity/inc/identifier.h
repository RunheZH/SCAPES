#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <QJsonObject>
#include "common_lib.h"

class Identifier
{
public:
    explicit Identifier(QString aName): name(aName){}
    QString getName() const {return name;}
    virtual QJsonObject toJSon() = 0;
    virtual ~Identifier() = default;

protected:
    QString name;
};

#endif
