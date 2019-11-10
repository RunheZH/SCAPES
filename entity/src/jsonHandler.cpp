#include "../inc/jsonHandler.h"

JsonHandler::JsonHandler()
{
    m_currentJsonObject = QJsonObject();
}

JsonHandler::JsonHandler(QString fileName)
{
    fileToHandle = fileName + ".json";
    qDebug() << fileToHandle;
    m_currentJsonObject = getJsonFromStr("{}");
}

JsonHandler::~JsonHandler(){}

QJsonObject JsonHandler::getJsonFromStr(QString jsonString)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject jsonObject = jsonDocument.object();
    return jsonObject;
}

QJsonObject JsonHandler::getJsonObj(QString key, QString value)
{
    QJsonObject jsonObject;
    jsonObject.insert(key, value);
    return jsonObject;
}

QJsonObject JsonHandler::getJsonObj(QString key, QJsonObject value)
{
    QJsonObject jsonObject;
    jsonObject.insert(key, value);
    return jsonObject;
}

QJsonObject JsonHandler::findLabel(QString labelName)
{
    ResultState res = readData();
    if (res == ResultState::NO_ERROR) {
        if (m_currentJsonObject.contains("label")) {
            QJsonObject labelObj = m_currentJsonObject["label"].toObject();
            if (labelObj.contains(labelName)) {
                QJsonObject foundLabel = labelObj[labelName].toObject();
                return foundLabel;
            }
        }
    }
    return getJsonFromStr("{}");
}

QJsonObject JsonHandler::findVariable(QString variableName)
{
    ResultState res = readData();
    if (res == ResultState::NO_ERROR) {
        if (m_currentJsonObject.contains("variable")) {
            QJsonObject variableObj = m_currentJsonObject["variable"].toObject();
            if (variableObj.contains(variableName)) {
                QJsonObject foundVar = variableObj[variableName].toObject();
                return foundVar;
            }
        }
    }
    return getJsonFromStr("{}");
}

ResultState JsonHandler::addElement(QString elementType, QString key, QJsonObject valueObj)
{
    ResultState res = readData();
    if (res != ResultState::NO_ERROR) {
        return res;
    }

    if (!m_currentJsonObject.contains(elementType)){
        m_currentJsonObject.insert(elementType, QJsonObject());
    }
    QJsonObject elementObj = m_currentJsonObject[elementType].toObject();

    elementObj.insert(key, valueObj);
    m_currentJsonObject.insert(elementType, elementObj);
    res = writeData(m_currentJsonObject);
    return res;
}

ResultState JsonHandler::readData()
{
    QFile file(fileToHandle);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QString source = file.readAll();
    QJsonDocument data = QJsonDocument::fromJson(source.toUtf8());
    m_currentJsonObject = data.object();

    file.close();
    return NO_ERROR;
}

ResultState JsonHandler::writeData(QJsonObject jsonObj)
{
    QFile file(fileToHandle);
    if (!file.open(QFile::WriteOnly | QFile::Append | QFile::Text | QFile::Truncate)) {
        qDebug() << "WRITE: cannot open file";
        return FILE_OPEN_ERROR;
    }
    QJsonDocument aQJsonDocument;
    aQJsonDocument.setObject(jsonObj);
    file.write(aQJsonDocument.toJson());

    file.close();
    return NO_ERROR;
}
