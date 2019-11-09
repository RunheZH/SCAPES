#include "../inc/compStmt.h"
#include "../../inc/jsonHandler.h"

#include<QApplication>
#include<QDebug>

CompStmt::CompStmt(QString pgmName, QString stmt, Label* lbl) : Statement(pgmName, stmt, lbl)
{
    qDebug() << "CompStmt()";
}

CompStmt::~CompStmt()
{
    qDebug() << "~CompStmt()";
}

ResultState CompStmt::compile()
{
    qDebug() << "CompStmt.compile()";
    QStringList args = this->statement.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if (args.size() != 3){
        if(args.size() == 1){
            return NO_OPERAND_ONE_ERROR;
        }
        if(args.size() == 2){
            return NO_OPERAND_TWO_ERROR;
        }
        else {
            return OPERAND_NUMBER_EXCEED_ERROR;
        }
    }

    QString instruction = args[0];
    QString operand1 = args[1];
    QString operand2 = args[2];

    JsonHandler* aJson = new JsonHandler(this->programName);
    QJsonObject firstQJsonObject = aJson->findVariable(operand1, TypeE::INT);
    QJsonObject secondQJsonObject = aJson->findVariable(operand2, TypeE::INT);

    // Variable 1 found
    if (firstQJsonObject != aJson->getJsonFromStr("{}")){
        // Variable 2 found
        if (secondQJsonObject != aJson->getJsonFromStr("{}")){
            delete(aJson);
            return NO_ERROR;
        }
        // Variable 2 NOT found
        else {
            delete(aJson);
            return VARIABLE_TWO_NOT_FOUND_ERROR;
        }
    }
    // Variable 1 NOT found
    else{
        // Variable 2 found
        if (secondQJsonObject != aJson->getJsonFromStr("{}")){
            delete(aJson);
            return VARIABLE_ONE_NOT_FOUND_ERROR;
        }
        // Variable 2 NOT found
        else {
            delete(aJson);
            return VARIABLE_ONE_AND_TWO_NOT_FOUND_ERROR;
        }
    }
}

ResultState CompStmt::run()
{
    qDebug() << "CompStmt.run()";
    return NO_ERROR;
}
