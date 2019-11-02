#ifndef JMP_STMT_H
#define JMP_STMT_H

#include <string>
#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class JumpStmt : public Statement
{
public:
    JumpStmt(string programName, string statement);
    ~JumpStmt();
    ResultState compile(string stmt);
    ResultState run(string stmt);

private:
    // add helper functions
};

#endif