#ifndef CMP_STMT_H
#define CMP_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"
#include "../../inc/jsonHandler.h"

class CompStmt : public Statement
{
public:
    CompStmt(QString programName, QString statement, QMap<QString, std::shared_ptr<Identifier>>& ids, int lineNum);
    ~CompStmt();
    ResultState compile();
    ReturnValue* run();

private:
    Operand op1;
    Operand op2;
};

#endif
