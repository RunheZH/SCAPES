#ifndef JEQ_STMT_H
#define JEQ_STMT_H

#include <string>
#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class JEqStmt : public Statement
{
public:
    JEqStmt(string programName, string statement);
    ~JEqStmt();
    ResultState compile(string stmt);
    ResultState run(string stmt);

private:
    // add helper functions
};

#endif