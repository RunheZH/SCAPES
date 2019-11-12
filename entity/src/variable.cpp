#include "../inc/variable.h"
#include "../inc/jsonHandler.h"

Variable::Variable(QString variableName, TypeE type) : Identifier(variableName)
{
    this->type = type;
    this->value = "undefined";
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

    JsonHandler jsonHdlr;
    QJsonObject varObj = QJsonObject();
    varObj = jsonHdlr.appendToEnd(varObj, jsonHdlr.getJsonObj("type", typeToWrite));
    varObj = jsonHdlr.appendToEnd(varObj, jsonHdlr.getJsonObj("value", value));

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

