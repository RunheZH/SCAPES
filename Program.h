#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <string>
#include "CommonLib.h"

using namespace std; 

class Program
{
public:
	Program(string ProgramName);
	ResultState compile(string programString);
	ResultState compileSingle(StatementId aStatementId, string statement);

private:
	string m_programName;
	std::map<StatementId, Statement*> m_statementMap;
};

#endif

