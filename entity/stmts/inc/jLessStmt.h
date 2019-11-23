#ifndef JLS_STMT_H
#define JLS_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class JLessStmt : public Statement
{
public:
    JLessStmt(QString programName, QString statement, Label* label, qint16 lineNum);
    ~JLessStmt();
    ResultState compile();
    ResultState run();

private:
    // add helper functions
    Operand* op1;
};

#endif
