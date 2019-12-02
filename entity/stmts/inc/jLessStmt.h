#ifndef JLS_STMT_H
#define JLS_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class JLessStmt : public Statement
{
public:
    JLessStmt(QString programName, QString statement, QMap<QString, std::shared_ptr<Identifier>>& ids, int lineNum);
    ~JLessStmt();
    ResultState compile();
    ReturnValue* run();

private:
    // add helper functions
    Operand op1;
};

#endif
