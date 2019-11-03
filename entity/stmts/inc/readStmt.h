#ifndef RDI_STMT_H
#define RDI_STMT_H

#include <string>
#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class ReadStmt : public Statement
{
public:
    ReadStmt(string programName, string statement);
    ~ReadStmt();
    ResultState compile(string stmt);
    ResultState run(string stmt);

private:
    // add helper functions
};

#endif