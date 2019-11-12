#ifndef PRT_STMT_H
#define PRT_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"
#include "../../inc/jsonHandler.h"

class PrintStmt : public Statement
{
public:
    PrintStmt(QString programName, QString statement, Label* label, qint16 lineNum);
    ~PrintStmt();
    ResultState compile();
    ResultState run();

private:
    Operand* op1;
};

#endif
