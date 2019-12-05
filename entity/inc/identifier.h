#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <QJsonObject>
#include "common_lib.h"

class Identifier
{
public:
    Identifier(QString programName, QString identifierName);
    virtual ~Identifier();
    QString getName();
    virtual QJsonObject toJSON() = 0;

protected:
    QString name;
    QString programName;
};

#endif
