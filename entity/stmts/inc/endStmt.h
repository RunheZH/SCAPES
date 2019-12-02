#ifndef END_STMT_H
#define END_STMT_H

#include "../../inc/common_lib.h"
#include "../../inc/statement.h"

class EndStmt : public Statement
{
public:
    EndStmt(QString programName, QString statement, QMap<QString, std::shared_ptr<Identifier>>& ids, int lineNum);
    ~EndStmt();
    ResultState compile();
    ReturnValue* run();

private:
    // add helper functions
};

#endif
