#include "../inc/variable.h"
#include "../inc/jsonHandler.h"

Variable::Variable(QString variableName, TypeE type) : Identifier(variableName)
{
    this->type = type;
    this->value = "undefined";
    valueSet = JsonHandler::getJsonFromStr("{}");
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
    varObj = JsonHandler::appendToEnd(varObj, JsonHandler::getJsonObj("value", valueSet));

    return varObj;
}

void Variable::setValue(QString value)
{
    this->value = value;
}

void Variable::setType(TypeE type)
{
    this->type = type;
}

QString Variable::getValue()
{
    return this->value;
}

TypeE Variable::getType()
{
    return type;
}

