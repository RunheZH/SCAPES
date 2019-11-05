#include "../inc/printStmt.h"
#include "../../src/jsonHandler.cpp"

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

    // Variable 1 found
    if (JsonHandler::findVariable(operand1, INT)){
        return NO_ERROR;
    }
    // Variable 1 not found
    else{
        return VARIABLE_ONE_NOT_FOUND_ERROR;
    }
}

ResultState PrintStmt::run()
{
    //return NO_ERROR;
}
