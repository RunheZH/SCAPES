#include "../inc/printStmt.h"

PrintStmt::PrintStmt(QString programName, QString statement, Label* label) : Statement(programName, statement, label)
{
}

PrintStmt::~PrintStmt()
{
}

ResultState PrintStmt::compile()
{
}

ResultState PrintStmt::run()
{
}
