#include "../inc/addStmt.h"

AddStmt::AddStmt(QString programName, QString statement, Label* label) : Statement(programName, statement, label)
{
    QStringList args = this->statement.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    this->op1 = new Operand(args[1]);
    this->op2 = new Operand(args[2]);
}

AddStmt::~AddStmt()
{}

ResultState AddStmt::compile()
{}

ResultState AddStmt::run()
{}
