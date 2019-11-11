#include "../inc/statement.h"

//static Logger* m_logger = Logger::getInstance("statement");

Statement::Statement(QString programName, QString statement, Label* label, qint16 lineNum)
{
    this->programName = programName;
    this->statement = statement;
    this->label = label;
    this->lineNum = lineNum;
}

Statement::~Statement()
{}
