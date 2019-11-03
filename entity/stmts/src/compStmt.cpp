#include "../inc/compStmt.h"

CompStmt::CompStmt(string programName, string statement) : Statement(programName, statement)
{
}

CompStmt::~CompStmt()
{
}

ResultState CompStmt::compile(string stmt)
{
}

ResultState CompStmt::run(string stmt)
{
}