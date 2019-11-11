#include "../inc/movStmt.h"

MovStmt::MovStmt(QString pgmName, QString stmt, Label* lbl, qint16 lnNum) : Statement(pgmName, stmt, lbl, lnNum)
{
    qDebug() << "MovStmt()";
}

MovStmt::~MovStmt()
{
    qDebug() << "~MovStmt()";
}

ResultState MovStmt::compile()
{
    qDebug() << "MovStmt.compile()";
    return NO_ERROR;
}

ResultState MovStmt::run()
{
    qDebug() << "MovStmt.run()";
    return NO_ERROR;
}
