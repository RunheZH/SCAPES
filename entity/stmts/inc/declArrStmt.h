#ifndef DCA_STMT_H
#define DCA_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class DeclArrStmt : public Statement
{
public:
    DeclArrStmt(QString programName, QString statement, Label* label, qint16 lineNum);
    ~DeclArrStmt();
    ResultState compile();
    ReturnValue* run();

private:
    // add helper functions
    Operand op1;
};

#endif
