#ifndef DCI_STMT_H
#define DCI_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"
#include "../../inc/jsonHandler.h"
#include "../../inc/variable.h"

class DeclIntStmt : public Statement
{
public:
    DeclIntStmt(QString programName, QString statement, Label* label, qint16 lineNum);
    ~DeclIntStmt();
    ResultState compile();
    ResultState run();

private:
    // add helper functions
    Variable* op1;
};

#endif
