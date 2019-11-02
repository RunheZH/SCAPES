#ifndef JLS_STMT_H
#define JLS_STMT_H

#include <string>
#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class JLessStmt : public Statement
{
public:
    JLessStmt(string programName, string statement);
    ~JLessStmt();
    ResultState compile(string stmt);
    ResultState run(string stmt);

private:
    // add helper functions
};

#endif