#ifndef JMP_STMT_H
#define JMP_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class JumpStmt : public Statement
{
public:
    JumpStmt(QString programName, QString statement, QMap<QString, std::shared_ptr<Identifier>>& ids, int lineNum);
    ~JumpStmt();
    ResultState compile();
    ReturnValue* run();

private:
    // add helper functions
    Operand op1;
};

#endif
