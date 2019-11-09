#include "../inc/addStmt.h"

AddStmt::AddStmt(QString pgmName, QString stmt, Label* lbl) : Statement(pgmName, stmt, lbl)
{
    qDebug() << "AddStmt()";
    QStringList args = this->statement.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    this->op1 = new Operand(args[1]);
    this->op2 = new Operand(args[2]);
}

AddStmt::~AddStmt()
{
    qDebug() << "~AddStmt()";
}

ResultState AddStmt::compile()
{
    qDebug() << "AddStmt.compile()";
    return NO_ERROR;
}

ResultState AddStmt::run()
{
    qDebug() << "AddStmt.run()";
    return NO_ERROR;
}
