#include "../inc/DBManager.h"

DBManager::DBManager(QString programName)
{
    this->dbName = programName + ".db";
}

DBManager::~DBManager(){}

void DBManager::createDB()
{
    if (QFile::exists(this->dbName))
    {
        QFile dbFile(this->dbName);
        dbFile.remove();
    }
    qDebug() << "creating DB...";
    this->createAConnection();
    this->createVariableTable();
    this->closeDB();
    qDebug() << "DB created successfully!";
}

void DBManager::createVariableTable()
{
    qDebug() << "creating variable table...";
    QSqlQuery query(QSqlDatabase::database());
    query.exec("CREATE TABLE variable (varName CHAR(256) PRIMARY KEY, value INT, type CHAR(5))");
    qDebug() << "variable table is created successfully";
}

void DBManager::addLabel(QString labelName, int lineNum)
{
    // TODO
}

void DBManager::addVariable(QString variableName, TypeE type)
{
    qDebug() << "adding a new variable...";
    this->createAConnection();
    QSqlQuery query(QSqlDatabase::database());
    query.exec("INSERT INTO variable VALUES( '" + variableName + "', -1, '" + QString::number(type) + "')");
    this->closeDB();
}

void DBManager::createAConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(this->dbName);
    db.setHostName("localhost");
    db.open();
}

void DBManager::closeDB()
{
    {
        QSqlDatabase::database().close();
    }
    QSqlDatabase::removeDatabase("QSQLITE");
}
