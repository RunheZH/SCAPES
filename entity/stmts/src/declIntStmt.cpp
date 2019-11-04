#include "../inc/declIntStmt.h"

DeclIntStmt::DeclIntStmt(QString programName, QString statement, Label* label) : Statement(programName, statement, label)
{
}

DeclIntStmt::~DeclIntStmt()
{
}

ResultState DeclIntStmt::compile()
{
}

ResultState DeclIntStmt::run()
{
}
