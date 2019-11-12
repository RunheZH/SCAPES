#ifndef ADD_STMT_H
#define ADD_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"
#include "../../inc/operand.h"

class AddStmt : public Statement
{
public:
    AddStmt(QString programName, QString statement, Label* label, qint16 lineNum);
    ~AddStmt();
    ResultState compile();
    ResultState run();

private:
};

#endif
