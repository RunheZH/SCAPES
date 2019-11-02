#ifndef ADD_STMT_H
#define ADD_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class AddStmt : public Statement
{
public:
    AddStmt(string programName, string statement);
    ~AddStmt();
    ResultState compile(string stmt);
    ResultState run(string stmt);

private:
    // add helper functions
};

#endif