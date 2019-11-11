#ifndef STATEMENT_H
#define STATEMENT_H

#include "common_lib.h"
#include "operand.h"
#include "label.h"

class Statement
{
public:
    Statement(QString programName, QString statement, Label* label, qint16 lineNum);
	virtual ~Statement();
    virtual ResultState compile() = 0;
    virtual ResultState run() = 0;

protected:
    QString programName;
    QString statement;
    Label*  label;
    qint16  lineNum;
};

#endif
