#include "../inc/jumpStmt.h"

JumpStmt::JumpStmt(QString pgmName, QString stmt, Label* lbl, qint16 lnNum) : Statement(pgmName, stmt, lbl, lnNum)
{
    qDebug() << "JumpStmt()";
}

JumpStmt::~JumpStmt()
{
    qDebug() << "~JumpStmt()";
}

ResultState JumpStmt::compile()
{
    qDebug() << "JumpStmt.compile()";

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

ResultState JumpStmt::run()
{
    qDebug() << "JumpStmt.run()";
    return NO_ERROR;
}
