#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "common_lib.h"
#include "variable.h"
#include "label.h"

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
    Label* findLabel(QString labelName);
    Variable* findVariable(QString variableName);
    ResultState addElement(QString elementType, QString key, QJsonObject valueObj);

private:
    void readData();
    ResultState writeData(QJsonObject jsonObj);

    QString fileToHandle;
    QJsonObject m_currentJsonObject;
};

#endif // JSONHANDLER_H
