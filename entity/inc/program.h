#ifndef PROGRAM_H
#define PROGRAM_H

#include "common_lib.h"
#include "identifier.h"
#include "statement.h"
#include "../../control/inc/compileControl.h"

class Program
{
public:
	Program(string programName, string pgmScript);
	~Program();
	ResultState save();
	ResultState compile();
	ResultState run();
	//ResultState compileSingle(Identifier stmtID, string aStmt);

private:
	string programName;
	string pgmScript;
	Identifier** ids;
	Statement**  statements;
	//std::map<StatementId, Statement*> m_statementMap;
};

#endif

