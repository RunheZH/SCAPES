#ifndef RDI_STMT_H
#define RDI_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"
#include "../../../control/inc/errorControl.h"

class ReadStmt : public Statement
{
public:
    ReadStmt(QString programName, QString statement, QMap<QString, std::shared_ptr<Identifier>>& ids,
             int lineNum, ErrorControl* errorControl);
    ~ReadStmt();
    ResultState compile();
    ReturnValue* run();

private:
    ResultState checkVariable(QString &Qop, Operand &op, bool checkLiteral=false); //override
    Operand op1;
    ErrorControl* errorControl;
};

#endif
