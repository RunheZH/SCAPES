#include "../inc/jEqStmt.h"

JEqStmt::JEqStmt(QString programName, QString statement, Label* label) : Statement(programName, statement, label)
{
}

JEqStmt::~JEqStmt()
{
}

ResultState JEqStmt::compile()
{
}

ResultState JEqStmt::run()
{
}
