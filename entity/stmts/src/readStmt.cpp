#include "../inc/readStmt.h"

ReadStmt::ReadStmt(QString programName, QString statement, Label* label) : Statement(programName, statement, label)
{
}

ReadStmt::~ReadStmt()
{
}

ResultState ReadStmt::compile()
{
}

ResultState ReadStmt::run()
{
}
