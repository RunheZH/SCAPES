#include "../inc/compStmt.h"
#include "../../src/jsonHandler.cpp"

CompStmt::CompStmt(QString programName, QString statement, Label* label) : Statement(programName, statement, label)
{
}

CompStmt::~CompStmt()
{
}

ResultState CompStmt::compile()
{
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

//    // Variable 1 found
//    if (JsonHandler::findVariable(operand1, INT)){
//        // Variable 2 found
//        if (JsonHandler::findVariable(operand2, INT)){
//            return NO_ERROR;
//        }
//        // Variable 2 NOT found
//        else {
//            return VARIABLE_TWO_NOT_FOUND_ERROR;
//        }
//    }
//    // Variable 1 NOT found
//    else{
//        // Variable 2 found
//        if (JsonHandler::findVariable(operand2, INT)){
//            return VARIABLE_ONE_NOT_FOUND_ERROR;
//        }
//        // Variable 2 NOT found
//        else {
//            return VARIABLE_ONE_AND_TWO_NOT_FOUND_ERROR;
//        }
//    }
    return NO_ERROR;
}

ResultState CompStmt::run()
{
    //return NO_ERROR;
}
