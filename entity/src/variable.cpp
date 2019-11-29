#include "../inc/variable.h"
#include "../inc/jsonHandler.h"

Variable::Variable(QString pgmName, QString variableName, TypeE type, int maxSize) : Identifier(pgmName, variableName)
{
    this->type = type;
    this->maxSize = maxSize;
}

Variable::~Variable(){}

QJsonObject Variable::toJSON()
{
    QString typeToWrite;
    if (type == INT)
        typeToWrite = "int";
    else if (type == ARRAY)
        typeToWrite = "array";
    else
        typeToWrite = "undefined";

    QJsonObject varObj = QJsonObject();
    varObj = JsonHandler::appendToEnd(varObj, JsonHandler::getJsonObj("type", typeToWrite));
    if (type == ARRAY) {
        varObj = JsonHandler::appendToEnd(varObj, JsonHandler::getJsonObj("size", QString::number(maxSize)));
        QJsonObject valueArray = QJsonObject();
        for(int i = 0; i < maxSize; i++) {
            valueArray.insert(QString::number(i), QString::number(false));
        }
        varObj = JsonHandler::appendToEnd(varObj, JsonHandler::getJsonObj("initialized?", valueArray));
    }

    return varObj;
}

void Variable::addToDB()
{
    DBManager db(this->programName);
    db.addVariable(this->getName(), INT);
}

TypeE Variable::getType()
{
    return type;
}

int Variable::getSize()
{
    return maxSize;
}

bool Variable::setValue(int aValue, int position)
{
    if (type != ARRAY && position != 0) {
        return false;
    }
    if (value.size() < position) {
        return false;
    } else if (value.size() == position) {
        value.append(aValue);
    } else {
        value[position] = aValue;
    }
    return true;
}

QString Variable::getValue()
{
    QString aValue;
    if (value.size()==0) {
        aValue = "undefined";
    } else if (value.size()==1) {
        aValue = QString::number(value[0]);
    } else {
        aValue += "[" + QString::number(value[0]);
        for(int i = 1; i < value.size(); ++i) {
            aValue += ", " + QString::number(value[i]);
        }
        aValue += "]";
    }
    return aValue;
}

QString Variable::getValue(int position)
{
    if (value.size() < position) {
        return "undefined";
    }
    return QString::number(value[position]);
}
