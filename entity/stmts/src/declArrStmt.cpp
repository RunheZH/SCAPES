#include "../inc/declArrStmt.h"

DeclArrStmt::DeclArrStmt(QString pgmName, QString stmt, Label* lbl) : Statement(pgmName, stmt, lbl)
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
