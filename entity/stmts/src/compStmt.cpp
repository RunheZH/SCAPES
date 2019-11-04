#include "../inc/compStmt.h"

CompStmt::CompStmt(QString programName, QString statement, Label* label) : Statement(programName, statement, label)
{
}

CompStmt::~CompStmt()
{
}

ResultState CompStmt::compile()
{
}

ResultState CompStmt::run()
{
}
