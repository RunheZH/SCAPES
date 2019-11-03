#ifndef DCI_STMT_H
#define DCI_STMT_H

#include <string>
#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class DeclIntStmt : public Statement
{
public:
    DeclIntStmt(string programName, string statement);
    ~DeclIntStmt();
    ResultState compile(string stmt);
    ResultState run(string stmt);

private:
    // add helper functions
};

#endif