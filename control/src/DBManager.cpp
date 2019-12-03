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
    this->createAConnection();
    this->createVariableTable();
    this->createLabelTable();
    this->closeDB();
}

void DBManager::addLabel(QString labelName, int lineNum)
{
    this->createAConnection();
    QSqlQuery query(QSqlDatabase::database());
    query.exec("INSERT INTO label VALUES( '" + labelName + "', " + QString::number(lineNum) +")");
    this->closeDB();
}

void DBManager::addVariable(QString variableName, TypeE type)
{
    this->createAConnection();
    QSqlQuery query(QSqlDatabase::database());
    query.exec("INSERT INTO variable VALUES( '" + variableName + "', -1, '" + QString::number(type) + "')");
    this->closeDB();
}

void DBManager::setVariable(QString variableName, TypeE type, QVector<int> newValue)
{
    // TODO
}

void DBManager::setLabel(QString labelName, qint16 newLineNum)
{
    // TODO
}

QVector<int> DBManager::getVariableValue(QString variableName)
{
    // TODO
}

TypeE DBManager::getVariableType(QString varaibleName)
{
    // TODO
}

int DBManager::getVariableSize(QString variableName)
{
    // TODO
}

qint16 DBManager::getLabelLineNum(QString labelName)
{
    // TODO
}

void DBManager::removeVariable(QString variableName, TypeE type)
{
    // TODO
}

void DBManager::removeLabel(QString labelName)
{
    // TODO
}

void DBManager::createVariableTable()
{
    QSqlQuery query(QSqlDatabase::database());
    query.exec("CREATE TABLE variable (varName CHAR(256) PRIMARY KEY, value INT, type CHAR(5))");
}

void DBManager::createLabelTable()
{
    QSqlQuery query(QSqlDatabase::database());
    query.exec("CREATE TABLE label (labelName CHAR(256) PRIMARY KEY, lineNum INT)");
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
