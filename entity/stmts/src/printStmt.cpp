#include "../inc/printStmt.h"
#include "../../inc/jsonHandler.h"

#include<QApplication>
#include<QDebug>


PrintStmt::PrintStmt(QString pgmName, QString stmt, Label* lbl, qint16 lnNum) : Statement(pgmName, stmt, lbl, lnNum)
{
    qDebug() << "PrintStmt()";
}

PrintStmt::~PrintStmt()
{
    qDebug() << "~PrintStmt()";
}

ResultState PrintStmt::compile()
{
    qDebug() << "PrintStmt.compile()";
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

ResultState PrintStmt::run()
{
    qDebug() << "PrintStmt.run()";
    return NO_ERROR;
}
