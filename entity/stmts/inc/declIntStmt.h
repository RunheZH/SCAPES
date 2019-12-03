#ifndef DCI_STMT_H
#define DCI_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class DeclIntStmt : public Statement
{
public:
    DeclIntStmt(QString programName, QString statement, QMap<QString, std::shared_ptr<Identifier>>& ids, int lineNum);
    ~DeclIntStmt();
    ResultState compile();
    ReturnValue* run();

private:
    // add helper functions
    Operand op1;
};

#endif
