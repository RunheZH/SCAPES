#include "../inc/addStmt.h"

AddStmt::AddStmt(string programName, string statement) : Statement(programName, statement)
{}

AddStmt::~AddStmt()
{}

ResultState AddStmt::compile(string stmt)
{}

ResultState AddStmt::run(string stmt)
{}