#include "../inc/jLessStmt.h"

JLessStmt::JLessStmt(QString pgmName, QString stmt, Label* lbl, qint16 lnNum) : Statement(pgmName, stmt, lbl, lnNum)
{
    qDebug() << "JLessStmt()";
}

JLessStmt::~JLessStmt()
{
    qDebug() << "~JLessStmt()";
}

ResultState JLessStmt::compile()
{
    qDebug() << "JLessStmt.compile()";
    return NO_ERROR;
}

ResultState JLessStmt::run()
{
    qDebug() << "JLessStmt.run()";
    return NO_ERROR;
}
