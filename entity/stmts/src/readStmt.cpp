#include "../inc/readStmt.h"
#include "../../src/jsonHandler.cpp"

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

    // Variable 1 found
    if (JsonHandler::findVariable(operand1, INT)){
        return NO_ERROR;
    }
    // Variable 1 Not found
    else{
        return VARIABLE_ONE_NOT_FOUND_ERROR;
    }
}

ResultState ReadStmt::run()
{
    //return NO_ERROR;
}
