#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "common_lib.h"

class JsonHandler
{
public:
    JsonHandler();
    JsonHandler(QString fileName);
    ~JsonHandler();
    QJsonObject getJsonFromStr(QString jsonString);
    QJsonObject getJsonObj(QString key, QString value);
    QJsonObject getJsonObj(QString key, QJsonObject value);
    QJsonObject appendToEnd(QJsonObject first, QJsonObject second);
    QJsonObject findLabel(QString labelName);
    QJsonObject findVariable(QString variableName);
    ResultState addElement(QString elementType, QString key, QJsonObject valueObj);

private:
    ResultState readData();
    ResultState writeData(QJsonObject jsonObj);

    QString fileToHandle;
    QJsonObject m_currentJsonObject;
};

#endif // JSONHANDLER_H
