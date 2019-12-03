#ifndef JEQ_STMT_H
#define JEQ_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class JEqStmt : public Statement
{
public:
    JEqStmt(QString programName, QString statement, QMap<QString, std::shared_ptr<Identifier>>& ids, int lineNum);
    ~JEqStmt();
    ResultState compile();
    ReturnValue* run();

private:
    // add helper functions
    Operand op1;
};

#endif
