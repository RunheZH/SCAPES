#include "../inc/jMoreStmt.h"

JMoreStmt::JMoreStmt(QString pgmName, QString stmt, Label* lbl, qint16 lnNum) : Statement(pgmName, stmt, lbl, lnNum)
{
    qDebug() << "JMoreStmt()";
}

JMoreStmt::~JMoreStmt()
{
    qDebug() << "~JMoreStmt()";
}

ResultState JMoreStmt::compile()
{
    qDebug() << "JMoreStmt.compile()";
    QStringList args = this->statement.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if (args.size() != 2){
        if(args.size() == 1){
            return NO_OPERAND_ONE_ERROR;
        }
        else {
            return OPERAND_NUMBER_EXCEED_ERROR;
        }
    }

    QString instruction = args[0];
    QString label = args[1];
    return NO_ERROR;
}

ResultState JMoreStmt::run()
{
    qDebug() << "JMoreStmt.run()";
    return NO_ERROR;
}
