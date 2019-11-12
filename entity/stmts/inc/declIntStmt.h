#ifndef DCI_STMT_H
#define DCI_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class DeclIntStmt : public Statement
{
public:
    DeclIntStmt(QString programName, QString statement, Label* label, qint16 lineNum);
    ~DeclIntStmt();
    ResultState compile();
    ResultState run();

private:
    // add helper functions
    Operand* op1;
};

#endif
