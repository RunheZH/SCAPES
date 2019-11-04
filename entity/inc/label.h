#ifndef LABEL_H
#define LABEL_H

#include "common_lib.h"
#include "identifier.h"

class Label : public Identifier
{
public:
    Label(QString name);
    ~Label();
    QString getName();
    // and other getters, setters

private:
    QString name;
    TypeE type;
    QString value; // use string for now, change it later
};

#endif
