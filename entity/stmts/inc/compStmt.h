#ifndef CMP_STMT_H
#define CMP_STMT_H

#include <string>
#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class CompStmt : public Statement
{
public:
    CompStmt(string programName, string statement);
    ~CompStmt();
    ResultState compile(string stmt);
    ResultState run(string stmt);

private:
    // add helper functions
};

#endif