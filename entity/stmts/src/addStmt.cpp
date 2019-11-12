#include "../inc/addStmt.h"

AddStmt::AddStmt(QString pgmName, QString stmt, Label* lbl, qint16 lnNum) : Statement(pgmName, stmt, lbl, lnNum)
{
    qDebug() << "AddStmt()";
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
