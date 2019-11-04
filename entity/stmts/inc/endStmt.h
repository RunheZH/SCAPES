#ifndef END_STMT_H
#define END_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class EndStmt : public Statement
{
public:
    EndStmt(QString programName, QString statement, Label* label);
    ~EndStmt();
    ResultState compile();
    ResultState run();

private:
    // add helper functions
};

#endif
