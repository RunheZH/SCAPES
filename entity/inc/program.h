#ifndef PROGRAM_H
#define PROGRAM_H

#include "common_lib.h"
#include "identifier.h"
#include "statement.h"
#include "../stmts/inc/addStmt.h"
#include "../stmts/inc/compStmt.h"
#include "../stmts/inc/declArrStmt.h"
#include "../stmts/inc/declIntStmt.h"
#include "../stmts/inc/endStmt.h"
#include "../stmts/inc/jEqStmt.h"
#include "../stmts/inc/jLessStmt.h"
#include "../stmts/inc/jMoreStmt.h"
#include "../stmts/inc/jumpStmt.h"
#include "../stmts/inc/movStmt.h"
#include "../stmts/inc/printStmt.h"
#include "../stmts/inc/readStmt.h"
#include <QFile>
#include <QRegExp>

class Program
{
public:
    Program(QString, QString);
	~Program();
	ResultState save();
	ResultState compile();
    ResultState run();

private:
    QString pgmName;
    QString pgmPath;
    qint16  numStmt;
	Identifier** ids;
	Statement**  statements;

    // helper functions
    ResultState addStmt(QString);
    StatementId getStmtId(QString);
	//std::map<StatementId, Statement*> m_statementMap;
};

#endif

