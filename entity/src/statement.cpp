#include "../inc/statement.h"

//static Logger* m_logger = Logger::getInstance("statement");

Statement::Statement(string programName, string statement)
{
    this->programName = programName;
    this->statement = statement;
}

Statement::~Statement()
{}