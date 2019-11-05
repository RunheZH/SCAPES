#include "../inc/declIntStmt.h"


DeclIntStmt::DeclIntStmt(QString programName, QString statement, Label* label) : Statement(programName, statement, label)
{
}

DeclIntStmt::~DeclIntStmt()
{
}

ResultState DeclIntStmt::compile()
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
    return NO_ERROR;
}

ResultState DeclIntStmt::run()
{
  return NO_ERROR;
}

