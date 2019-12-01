#ifndef JMP_STMT_H
#define JMP_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class JumpStmt : public Statement
{
public:
    JumpStmt(QString programName, QString statement, Label* label, qint16 lineNum);
    ~JumpStmt();
    ResultState compile();
    ReturnValue* run();

private:
    // add helper functions
    Operand op1;
};

#endif
