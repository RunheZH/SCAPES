#include "../inc/jEqStmt.h"

JEqStmt::JEqStmt(QString pgmName, QString stmt, Label* lbl, qint16 lnNum) : Statement(pgmName, stmt, lbl, lnNum)
{
    qDebug() << "JEqStmt()";
}

JEqStmt::~JEqStmt()
{
    qDebug() << "~JEqStmt()";
}

ResultState JEqStmt::compile()
{
    qDebug() << "JEqStmt.compile()";
    return NO_ERROR;
}

ResultState JEqStmt::run()
{
    qDebug() << "JEqStmt.run()";
    return NO_ERROR;
}
