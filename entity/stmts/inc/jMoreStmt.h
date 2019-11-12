#ifndef JMR_STMT_H
#define JMR_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class JMoreStmt : public Statement
{
public:
    JMoreStmt(QString programName, QString statement, Label* label, qint16 lineNum);
    ~JMoreStmt();
    ResultState compile();
    ResultState run();

private:
    // add helper functions
    Operand* op1;
};

#endif
