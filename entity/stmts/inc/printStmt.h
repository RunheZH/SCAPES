#ifndef PRT_STMT_H
#define PRT_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"
#include "../../inc/jsonHandler.h"
#include "../../../control/inc/errorControl.h"

class PrintStmt : public Statement
{
public:
    PrintStmt(QString programName, QString statement, QMap<QString, std::shared_ptr<Identifier>>& ids,
              int lineNum, ErrorControl* errorControl);
    ~PrintStmt();
    ResultState compile();
    ReturnValue* run();

private:
    Operand op1;
    ErrorControl* errorControl;
};

#endif
