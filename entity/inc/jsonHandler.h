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
    static QJsonObject getJsonFromStr(QString jsonString);
    static QJsonObject getJsonObj(QString key, QString value);
    static QJsonObject getJsonObj(QString key, QJsonObject value);
    static QJsonObject appendToEnd(QJsonObject first, QJsonObject second);
    Label* findLabel(QString labelName);
    Variable* findVariable(QString variableName);
    ResultState addElement(QString elementType, QString key, QJsonObject valueObj);
    ResultState initArrayValue(QString variableName, int position);
    ResultState initIntValue(QString variableName);
    ResultState findInitArrayValue(QString variableName, int position);
    ResultState findInitIntValue(QString variableName);
    QJsonObject read();

private:
    void readData();
    ResultState writeData(QJsonObject jsonObj);

    QString programName;
    QString fileToHandle;
    QJsonObject m_currentJsonObject;
};

#endif // JSONHANDLER_H
