#ifndef LABEL_H
#define LABEL_H

#include "common_lib.h"
#include "identifier.h"

class Label : public Identifier
{
public:
    Label(QString labelName, qint16 stmtLineNum);
    ~Label();
    QJsonObject toJSON();

private:
    QString value; // use string for now, change it later
    qint16  stmtLineNum;
};

#endif
