#include "../inc/endStmt.h"

EndStmt::EndStmt(QString programName, QString statement, Label* label) : Statement(programName, statement, label)
{
}

EndStmt::~EndStmt()
{
}

ResultState EndStmt::compile()
{
}

ResultState EndStmt::run()
{
}
