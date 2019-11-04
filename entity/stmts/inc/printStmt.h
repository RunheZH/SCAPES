#ifndef PRT_STMT_H
#define PRT_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class PrintStmt : public Statement
{
public:
    PrintStmt(QString programName, QString statement, Label* label);
    ~PrintStmt();
    ResultState compile();
    ResultState run();

private:
    // add helper functions
};

#endif
