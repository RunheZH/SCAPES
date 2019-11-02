#ifndef END_STMT_H
#define END_STMT_H

#include <string>
#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class EndStmt : public Statement
{
public:
    EndStmt(string programName, string statement);
    ~EndStmt();
    ResultState compile(string stmt);
    ResultState run(string stmt);

private:
    // add helper functions
};

#endif