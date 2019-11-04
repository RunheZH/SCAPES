#ifndef JEQ_STMT_H
#define JEQ_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class JEqStmt : public Statement
{
public:
    JEqStmt(QString programName, QString statement, Label* label);
    ~JEqStmt();
    ResultState compile();
    ResultState run();

private:
    // add helper functions
};

#endif
