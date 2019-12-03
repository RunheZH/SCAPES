#ifndef ADD_STMT_H
#define ADD_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"
#include "../../inc/operand.h"

class AddStmt : public Statement
{
public:
    AddStmt(QString programName, QString statement, QMap<QString, std::shared_ptr<Identifier>>& ids, int lineNum);
    ~AddStmt();
    ResultState compile();
    ReturnValue* run();

private:
    Operand op1;
    Operand op2;
};

#endif
