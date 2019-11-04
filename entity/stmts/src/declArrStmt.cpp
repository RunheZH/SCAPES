#include "../inc/declArrStmt.h"

DeclArrStmt::DeclArrStmt(QString programName, QString statement, Label* label) : Statement(programName, statement, label)
{
}

DeclArrStmt::~DeclArrStmt()
{
}

ResultState DeclArrStmt::compile()
{
}

ResultState DeclArrStmt::run()
{
}
