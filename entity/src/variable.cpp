#include "../inc/variable.h"
#include "../inc/jsonHandler.h"

Variable::Variable(QString pgmName, QString variableName, TypeE type, int maxSize) : Identifier(pgmName, variableName)
{
    this->type = type;
    this->maxSize = maxSize;
    this->usedSize = 0;
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

int Variable::getUsedSize()
{
    return usedSize;
}

void Variable::setSize(int newSize)
{
    maxSize = newSize;
}

void Variable::setUsedSize(int newUsedSize)
{
    usedSize = newUsedSize;
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

    // pass the new value to the DB
    DBManager db(this->programName);
    db.setVariable(this->getName(),this->getType(),value);

    return true;
}

QVector<int> Variable::getValue()
{
    return value;
}

int Variable::getValue(int position)
{
    return value[position];
}
