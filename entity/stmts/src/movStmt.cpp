#include "../inc/movStmt.h"

MovStmt::MovStmt(QString programName, QString statement, Label* label) : Statement(programName, statement, label)
{
}

MovStmt::~MovStmt()
{
}

ResultState MovStmt::compile()
{
}

ResultState MovStmt::run()
{
}
