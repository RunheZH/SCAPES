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
    void setVariable(QString variableName, TypeE type, QVector<int> newValue);
    void setLabel(QString labelName, qint16 newLineNum);
    QVector<int> getVariableValue(QString variableName);
    TypeE getVariableType(QString varaibleName);
    int getVariableSize(QString variableName);
    qint16 getLabelLineNum(QString labelName);
    void removeVariable(QString variableName, TypeE type);
    void removeLabel(QString labelName);
    void createDB();

private:
    QString dbName;
    void createVariableTable();
    void createLabelTable();
    void createAConnection();
    void closeDB();
};

#endif // DBMANAGER_H
