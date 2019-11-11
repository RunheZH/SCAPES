#include "../inc/variable.h"

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

    JsonHandler jsonHdlr;
    QJsonObject varObj = QJsonObject();
    varObj = jsonHdlr.appendToEnd(varObj, jsonHdlr.getJsonObj("type", typeToWrite));
    varObj = jsonHdlr.appendToEnd(varObj, jsonHdlr.getJsonObj("value", value));

    return varObj;
}

void Variable::setValue(QString value, TypeE type)
{
    this->value = value;
    this->type  = type;
}

TypeE Variable::getType()
{
    return type;
}

