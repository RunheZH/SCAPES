#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include<QString>
#include <QJsonArray>
#include <QJsonObject>
#include "common_lib.h"

class JsonHandler
{
public:
    JsonHandler(QString fileName);
    QJsonObject JsonObjectFromString(QString jsonString);
    QJsonObject findLabel(QString labelName);
    QJsonObject findVariable(QString variableName, TypeE type);
    ResultState addElement(QString elementName, QJsonObject aQJsonObject);

private:
    JsonHandler(const JsonHandler&);
    void readData();
    void writeData();

    QString m_currentFile;
    ResultState m_currentResultState;
    QJsonObject m_currentJsonObject;
};

#endif // JSONHANDLER_H
