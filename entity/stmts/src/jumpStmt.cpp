#include "../inc/jumpStmt.h"

JumpStmt::JumpStmt(QString programName, QString statement, Label* label) : Statement(programName, statement, label)
{
}

JumpStmt::~JumpStmt()
{
}

ResultState JumpStmt::compile()
{
}

ResultState JumpStmt::run()
{
}
