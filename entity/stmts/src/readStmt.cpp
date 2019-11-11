#include "../inc/readStmt.h"

#include<QApplication>
#include<QDebug>

ReadStmt::ReadStmt(QString pgmName, QString stmt, Label* lbl, qint16 lnNum) : Statement(pgmName, stmt, lbl, lnNum)
{
    qDebug() << "ReadStmt()";
}

ReadStmt::~ReadStmt()
{
    qDebug() << "~ReadStmt()";
}

ResultState ReadStmt::compile()
{
    qDebug() << "ReadStmt.compile()";
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
    QString operand1 = args[1];
    ResultState res = NO_ERROR;

    JsonHandler* jsonHdlr = new JsonHandler(this->programName);
    QJsonObject aQJsonObject = jsonHdlr->findVariable(operand1);

    // Variable 1 not found
    if(aQJsonObject == jsonHdlr->getJsonFromStr("{}")){
        res = VARIABLE_ONE_NOT_FOUND_ERROR;
    }
    delete(jsonHdlr);
    return res;
}

ResultState ReadStmt::run()
{
    qDebug() << "ReadStmt.run()";
    return NO_ERROR;
}
