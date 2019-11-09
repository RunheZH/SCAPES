#include "../inc/endStmt.h"

EndStmt::EndStmt(QString pgmName, QString stmt, Label* lbl) : Statement(pgmName, stmt, lbl)
{
    qDebug() << "EndStmt()";
}

EndStmt::~EndStmt()
{
    qDebug() << "~EndStmt()";
}

ResultState EndStmt::compile()
{
    qDebug() << "EndStmt.compile()";

    QStringList args = this->statement.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if (args.size() != 1){
            return OPERAND_NUMBER_EXCEED_ERROR;
    }

    return NO_ERROR;
}

ResultState EndStmt::run()
{
    qDebug() << "EndStmt.run()";
    return NO_ERROR;
}
