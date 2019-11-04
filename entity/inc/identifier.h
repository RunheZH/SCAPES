#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "common_lib.h"

class Identifier
{
public:
    Identifier(QString name);
    virtual ~Identifier();
    virtual QString getName() = 0;

protected:
    QString name;
};

#endif
