#ifndef PRT_STMT_H
#define PRT_STMT_H

#include <string>
#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class PrintStmt : public Statement
{
public:
    PrintStmt(string programName, string statement);
    ~PrintStmt();
    ResultState compile(string stmt);
    ResultState run(string stmt);

private:
    // add helper functions
};

#endif