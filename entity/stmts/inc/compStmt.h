#ifndef CMP_STMT_H
#define CMP_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class CompStmt : public Statement
{
public:
    CompStmt(QString programName, QString statement, Label* label);
    ~CompStmt();
    ResultState compile();
    ResultState run();

private:
    // add helper functions
};

#endif
