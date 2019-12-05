#ifndef PROGRAM_H
#define PROGRAM_H

#include <QMap>
#include <QVector>
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
#include "../../control/inc/errorControl.h"

class Program
{

public:
    Program(QString programPath, OutputTabWidget* consoleTab, OutputTabWidget* errorTab);
    ~Program();
    ResultState save();
    ResultState loadFromJSON();
    ResultState compile(bool isLoadFromJSON = false);
    ResultState run();
    void printIdentifiers();

private:
    ErrorControl* errorControl;

    QString pgmName;
    QString tempFileName;
    QString pgmPath;
    int     cmpResult;
    int     jumpToLineNum;
    QMap<QString, std::shared_ptr<Identifier>> ids;
    QMap<int, Statement*> statements;
    QMap<int, Statement*> jumpStmts;

    bool hasEnd;
    bool hasError;

    // helper functions
    ResultState addStmt(QString stmt, int lineNum);
    StatementId getStmtId(QString ins);
    bool isEndStmt(Statement* stmt);
    bool isJumpStmt(Statement* stmt);
};

#endif
