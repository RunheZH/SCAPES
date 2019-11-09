#include "../inc/jLessStmt.h"

JLessStmt::JLessStmt(QString pgmName, QString stmt, Label* lbl) : Statement(pgmName, stmt, lbl)
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
