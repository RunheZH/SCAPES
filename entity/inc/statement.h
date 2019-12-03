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
    int getLineNum() {return this->lineNum;}

protected:
    virtual ResultState checkVariable(QString& operand, Operand& op, bool checkLiteral = false);
    ResultState getResultStateForTwoOp(ResultState resultState1, ResultState resultState2);
    QString programName;
    QString statement;
    QMap<QString, std::shared_ptr<Identifier>>& ids;
    Label* label;
    int lineNum;
};

#endif
