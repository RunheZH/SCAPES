#include "../inc/readStmt.h"

#include<QApplication>
#include<QDebug>

ReadStmt::ReadStmt(QString programName, QString statement, Label* label) : Statement(programName, statement, label)
{
}

ReadStmt::~ReadStmt()
{
}

ResultState ReadStmt::compile()
{
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

ResultState ReadStmt::run()
{
    //return NO_ERROR;
}
