#include "../inc/printStmt.h"
#include "../../inc/jsonHandler.h"

#include<QApplication>
#include<QDebug>


PrintStmt::PrintStmt(QString programName, QString statement, Label* label) : Statement(programName, statement, label)
{
}

PrintStmt::~PrintStmt()
{
}

ResultState PrintStmt::compile()
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

    JsonHandler aJson(QCoreApplication::applicationDirPath()+"/a.json");
    QJsonObject tQJsonObject = aJson.findVariable(operand1, TypeE::INT);

    // Variable 1 not found
    if(tQJsonObject == aJson.getJsonFromStr("{}")){
        return VARIABLE_ONE_NOT_FOUND_ERROR;
    }
    // Variable 1 found
    else {
        return NO_ERROR;
    }

}

ResultState PrintStmt::run()
{
    //return NO_ERROR;
}
