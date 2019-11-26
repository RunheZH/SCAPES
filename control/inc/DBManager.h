#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include "../../entity/inc/common_lib.h"

class DBManager
{
public:
    DBManager(QString programName);
    ~DBManager();
    void addLabel(QString labelName, int lineNum);
    void addVariable(QString variableName, TypeE type);
    void createDB();
    void createVariableTable();

private:
    QString dbName;
    void createAConnection();
    void closeDB();
};

#endif // DBMANAGER_H
