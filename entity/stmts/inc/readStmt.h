#ifndef RDI_STMT_H
#define RDI_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class ReadStmt : public Statement
{
public:
    ReadStmt(QString programName, QString statement, QMap<QString, std::shared_ptr<Identifier>>& ids, int lineNum);
    ~ReadStmt();
    ResultState compile();
    ReturnValue* run();

private:
    Operand op1;
};

#endif
