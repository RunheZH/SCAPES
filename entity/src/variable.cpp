#include "../inc/variable.h"
#include "../inc/jsonHandler.h"

Variable::Variable(QString variableName, TypeE type) : Identifier(variableName)
{
    this->type = type;
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

    return varObj;
}

TypeE Variable::getType()
{
    return type;
}

bool Variable::changeValue(int aValue, int position)
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

QVector<int> Variable::getValue()
{
    return value;
}

int Variable::getValue(int position)
{
    if (value.size() < position) {
        position = value.size() - 1;
    }
    return value[position];
}
