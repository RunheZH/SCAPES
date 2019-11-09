#include "../inc/printStmt.h"
#include "../../inc/jsonHandler.h"

#include<QApplication>
#include<QDebug>


PrintStmt::PrintStmt(QString pgmName, QString stmt, Label* lbl) : Statement(pgmName, stmt, lbl)
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

    JsonHandler* aJson = new JsonHandler(this->programName);
    QJsonObject aQJsonObject = aJson->findVariable(operand1, TypeE::INT);

    // Variable 1 not found
    if(aQJsonObject == aJson->getJsonFromStr("{}")){
        delete(aJson);
        return VARIABLE_ONE_NOT_FOUND_ERROR;
    }
    // Variable 1 found
    else {
        delete(aJson);
        return NO_ERROR;
    }

}

ResultState PrintStmt::run()
{
    qDebug() << "PrintStmt.run()";
    return NO_ERROR;
}
