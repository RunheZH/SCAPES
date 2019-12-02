#ifndef PRT_STMT_H
#define PRT_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"
#include "../../inc/jsonHandler.h"

class PrintStmt : public Statement
{
public:
    PrintStmt(QString programName, QString statement, QMap<QString, std::shared_ptr<Identifier>>& ids, int lineNum);
    ~PrintStmt();
    ResultState compile();
    ReturnValue* run();

private:
    Operand op1;
};

#endif
