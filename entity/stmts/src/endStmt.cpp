#include "../inc/endStmt.h"

EndStmt::EndStmt(QString programName, QString statement, Label* label) : Statement(programName, statement, label)
{
}

EndStmt::~EndStmt()
{
}

ResultState EndStmt::compile()
{
    QStringList args = this->statement.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if (args.size() != 1){
            return OPERAND_NUMBER_EXCEED_ERROR;
    }

    return NO_ERROR;
}

ResultState EndStmt::run()
{
}
