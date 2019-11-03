#ifndef JMR_STMT_H
#define JMR_STMT_H

#include <string>
#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class JMoreStmt : public Statement
{
public:
    JMoreStmt(string programName, string statement);
    ~JMoreStmt();
    ResultState compile(string stmt);
    ResultState run(string stmt);

private:
    // add helper functions
};

#endif