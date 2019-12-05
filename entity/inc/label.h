#ifndef LABEL_H
#define LABEL_H

#include "common_lib.h"
#include "identifier.h"

class Label : public Identifier
{
public:
    Label(QString programName, QString labelName, int stmtLineNum);
    ~Label();
    int getLineNum();
    QJsonObject toJSON();

private:
    QString value; // use string for now, change it later
    int  stmtLineNum;
};

#endif
