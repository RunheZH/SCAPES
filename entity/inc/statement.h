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
    Statement(QString programName, QString statement, QMap<QString, std::shared_ptr<Identifier>>& ids, int lineNum);
	virtual ~Statement();
    virtual ResultState compile() = 0;
    virtual ReturnValue* run() = 0;
    virtual int getLineNum() {return this->lineNum;}
    virtual ResultState checkOperand(QString &Qop, Operand& op);
    virtual ResultState checkTwoOperand(QString &Qop1, Operand& op1, QString &Qop2, Operand& op2, bool notAllow = true, bool checkInit = true);
    virtual ResultState getResultStateForTwo(ResultState resultState1, ResultState resultState2);

protected:
    QString programName;
    QString statement;
    QMap<QString, std::shared_ptr<Identifier>>& ids;
    Label* label;
    int lineNum;
};

#endif
