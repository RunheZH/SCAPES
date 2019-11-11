#ifndef RDI_STMT_H
#define RDI_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class ReadStmt : public Statement
{
public:
    ReadStmt(QString programName, QString statement, Label* label, qint16 lineNum);
    ~ReadStmt();
    ResultState compile();
    ResultState run();

private:
    // add helper functions
};

#endif
