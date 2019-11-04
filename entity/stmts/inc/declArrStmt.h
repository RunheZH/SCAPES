#ifndef DCA_STMT_H
#define DCA_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class DeclArrStmt : public Statement
{
public:
    DeclArrStmt(QString programName, QString statement, Label* label);
    ~DeclArrStmt();
    ResultState compile();
    ResultState run();

private:
    // add helper functions
};

#endif
