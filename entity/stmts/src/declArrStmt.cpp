#include "../inc/declArrStmt.h"

DeclArrStmt::DeclArrStmt(QString pgmName, QString stmt, Label* lbl, qint16 lnNum) : Statement(pgmName, stmt, lbl, lnNum)
{
    qDebug() << "DeclArrStmt()";
}

DeclArrStmt::~DeclArrStmt()
{
    qDebug() << "~DeclArrStmt()";
}

ResultState DeclArrStmt::compile()
{
    qDebug() << "DeclArrStmt().compile()";
    return NO_ERROR;
}

ResultState DeclArrStmt::run()
{
    qDebug() << "DeclArrStmt().run()";
    return NO_ERROR;
}
