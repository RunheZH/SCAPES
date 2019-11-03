#ifndef MOV_STMT_H
#define MOV_STMT_H

#include <string>
#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class MovStmt : public Statement
{
public:
    MovStmt(string programName, string statement);
    ~MovStmt();
    ResultState compile(string stmt);
    ResultState run(string stmt);

private:
    // add helper functions
};

#endif