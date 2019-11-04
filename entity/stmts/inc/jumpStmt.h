#ifndef JMP_STMT_H
#define JMP_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class JumpStmt : public Statement
{
public:
    JumpStmt(QString programName, QString statement, Label* label);
    ~JumpStmt();
    ResultState compile();
    ResultState run();

private:
    // add helper functions
};

#endif
