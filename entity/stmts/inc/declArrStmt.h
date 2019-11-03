#ifndef DCA_STMT_H
#define DCA_STMT_H

#include <string>
#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class DeclArrStmt : public Statement
{
public:
    DeclArrStmt(string programName, string statement);
    ~DeclArrStmt();
    ResultState compile(string stmt);
    ResultState run(string stmt);

private:
    // add helper functions
};

#endif