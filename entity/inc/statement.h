#ifndef STATEMENT_H
#define STATEMENT_H

#include "common_lib.h"
#include "operand.h"
#include "label.h"
#include "jsonHandler.h"
#include "variable.h"


class Statement
{
public:
    Statement(QString programName, QString statement, Label* label, qint16 lineNum);
	virtual ~Statement();
    virtual ResultState compile() = 0;
    virtual ResultState run() = 0;
    virtual qint16 getLineNum() {return this->lineNum;}

protected:
    QString programName;
    QString statement;
    Label*  label;
    qint16  lineNum;
};

#endif
