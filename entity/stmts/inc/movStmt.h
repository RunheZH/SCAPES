#ifndef MOV_STMT_H
#define MOV_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class MovStmt : public Statement
{
public:
    MovStmt(QString programName, QString statement, QMap<QString, std::shared_ptr<Identifier>>& ids, int lineNum);
    ~MovStmt();
    ResultState compile();
    ReturnValue* run();

private:
    Operand op1;
    Operand op2;
};

#endif
