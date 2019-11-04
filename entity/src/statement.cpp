#include "../inc/statement.h"

//static Logger* m_logger = Logger::getInstance("statement");

Statement::Statement(QString programName, QString statement, Label* label)
{
    this->programName = programName;
    this->statement = statement;
    this->label = label;
}

Statement::~Statement()
{}
