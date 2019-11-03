#include "../inc/readStmt.h"

ReadStmt::ReadStmt(string programName, string statement) : Statement(programName, statement)
{
}

ReadStmt::~ReadStmt()
{
}

ResultState ReadStmt::compile(string stmt)
{
}

ResultState ReadStmt::run(string stmt)
{
}