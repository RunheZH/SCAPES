#ifndef MOV_STMT_H
#define MOV_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class MovStmt : public Statement
{
public:
    MovStmt(QString programName, QString statement, Label* label, qint16 lineNum);
    ~MovStmt();
    ResultState compile();
    ReturnValue* run();

private:
    // add helper functions
    Operand* op1;
    Operand* op2;
};

#endif
