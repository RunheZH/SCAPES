#ifndef PROGRAM_H
#define PROGRAM_H

#include "common_lib.h"
#include "identifier.h"
#include "statement.h"

class Program
{
public:
    Program(QString pgmName, QString pgmPath);
	~Program();
	ResultState save();
	ResultState compile();
	ResultState run();
    //ResultState compileSingle(Identifier stmtID, QString aStmt);

private:
    QString pgmName;
    QString pgmPath;
	Identifier** ids;
	Statement**  statements;
	//std::map<StatementId, Statement*> m_statementMap;
};

#endif

