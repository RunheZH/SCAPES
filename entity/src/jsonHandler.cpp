#include <QJsonValue>
#include "../inc/jsonHandler.h"

JsonHandler::JsonHandler()
{
    m_currentJsonObject = QJsonObject();
}

JsonHandler::JsonHandler(QString fileName)
{
    programName = fileName;
    fileToHandle = programName + ".json";
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

QJsonObject JsonHandler::appendToEnd(QJsonObject firstObj, QJsonObject secondObj)
{
    for (QJsonObject::iterator it = secondObj.begin(); it != secondObj.end(); it++)
        firstObj.insert(it.key(), it.value());

    return firstObj;
}

Label* JsonHandler::findLabel(QString labelName)
{
    readData();
    if (m_currentJsonObject.contains(LABEL)) {
        QJsonObject labelObj = m_currentJsonObject[LABEL].toObject();
        if (labelObj.contains(labelName)) {
            Label* foundLabel = new Label(this->programName, labelName, labelObj.value(labelName).toInt());
            return foundLabel;
        }
    }
    return nullptr;
}

Variable* JsonHandler::findVariable(QString variableName)
{
    readData();
    if (m_currentJsonObject.contains(VAR)) {
        QJsonObject variableObj = m_currentJsonObject[VAR].toObject();
        if (variableObj.contains(variableName)) {
            Variable* foundVar;
            if (variableObj[variableName].toObject().value("type") == "int") {
                foundVar = new Variable(this->programName, variableName, INT);
            } else {
                foundVar = new Variable(this->programName, variableName, ARRAY, variableObj[variableName].toObject().value("size").toString().toInt());
            }
            return foundVar;
        }
    }
    return nullptr;
}

ResultState JsonHandler::addElement(QString elementType, QString key, QJsonObject valueObj)
{
    readData();
    if (!m_currentJsonObject.contains(elementType)){
        m_currentJsonObject.insert(elementType, QJsonObject());
    }
    QJsonObject elementObj = m_currentJsonObject[elementType].toObject();

    elementObj.insert(key, valueObj);
    m_currentJsonObject.insert(elementType, elementObj);
    return writeData(m_currentJsonObject);
}

ResultState JsonHandler::initArrayValue(QString variableName, int position)
{
    readData();
    if (m_currentJsonObject.contains(VAR)) {
        QJsonObject variableObj = m_currentJsonObject[VAR].toObject();
        if (variableObj.contains(variableName)) {
            QJsonObject valueObj = variableObj[variableName].toObject()["initialized?"].toObject();
            if (valueObj.contains(QString::number(position))) {
                valueObj.insert(QString::number(position), QString::number(true));
                QJsonObject variable = variableObj[variableName].toObject();
                variable.insert("initialized?", valueObj);
                variableObj.insert(variableName, variable);
                m_currentJsonObject.insert(VAR, variableObj);
                return writeData(m_currentJsonObject);
            }
        }
    }
    return VARIABLE_NOT_FOUND_ERROR;
}

ResultState JsonHandler::initIntValue(QString variableName)
{
    readData();
    if (m_currentJsonObject.contains(VAR)) {
        QJsonObject variableObj = m_currentJsonObject[VAR].toObject();
        if (variableObj.contains(variableName)) {
            QJsonObject variable = variableObj[variableName].toObject();
            variable.insert("initialized?", QString::number(true));
            variableObj.insert(variableName, variable);
            m_currentJsonObject.insert(VAR, variableObj);
            return writeData(m_currentJsonObject);
        }
    }
    return VARIABLE_NOT_FOUND_ERROR;
}

ResultState JsonHandler::findInitArrayValue(QString variableName, int position)
{
    readData();
    if (m_currentJsonObject.contains(VAR)) {
        QJsonObject variableObj = m_currentJsonObject[VAR].toObject();
        if (variableObj.contains(variableName)) {
            if (variableObj[variableName].toObject()["initialized?"].toObject().contains(QString::number(position))) {
                if (variableObj[variableName].toObject()["initialized?"].toObject().value(QString::number(position)).toString().toInt()) {
                    qDebug() << "NO_ERROR";
                    return NO_ERROR;
                }  else {
                    qDebug() << "VARIABLE_NOT_INIT_ERROR";
                    return VARIABLE_NOT_INIT_ERROR;
                }
            }
        }
    }
    qDebug() << "VARIABLE_NOT_FOUND_ERROR";
    return  VARIABLE_NOT_FOUND_ERROR;
}

ResultState JsonHandler::findInitIntValue(QString variableName)
{
    readData();
    if (m_currentJsonObject.contains(VAR)) {
        QJsonObject variableObj = m_currentJsonObject[VAR].toObject();
        if (variableObj.contains(variableName)) {
            if (variableObj[variableName].toObject().contains("initialized?")){
                qDebug() << "NO_ERROR";
                return NO_ERROR;
            } else {
                qDebug() << "VARIABLE_NOT_INIT_ERROR";
                return VARIABLE_NOT_INIT_ERROR;
            }
        }
    }
    qDebug() << "VARIABLE_NOT_FOUND_ERROR";
    return  VARIABLE_NOT_FOUND_ERROR;
}

QJsonObject JsonHandler::read()
{
    readData();
    return this->m_currentJsonObject;
}

void JsonHandler::readData()
{
    QFile file(fileToHandle);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QString source = file.readAll();
    QJsonDocument data = QJsonDocument::fromJson(source.toUtf8());
    m_currentJsonObject = data.object();

    file.close();
}

ResultState JsonHandler::writeData(QJsonObject jsonObj)
{
    QFile file(fileToHandle);
    if (!file.open(QFile::WriteOnly | QFile::Append | QFile::Text | QFile::Truncate)) {
        return FILE_OPEN_ERROR;
    }
    QJsonDocument aQJsonDocument;
    aQJsonDocument.setObject(jsonObj);
    file.write(aQJsonDocument.toJson());

    file.close();
    return NO_ERROR;
}
