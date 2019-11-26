#ifndef JEQ_STMT_H
#define JEQ_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class JEqStmt : public Statement
{
public:
    JEqStmt(QString programName, QString statement, Label* label, qint16 lineNum);
    ~JEqStmt();
    ResultState compile();
    ReturnValue* run();

private:
    // add helper functions
    Operand* op1;
};

#endif
