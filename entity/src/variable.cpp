#include "../inc/variable.h"
#include "../inc/jsonHandler.h"

Variable::Variable(QString variableName, TypeE type) : Identifier(variableName)
{
    this->type = type;
}

Variable::~Variable(){}

QJsonObject Variable::toJSON()
{
    QString jsonString = "{\"name\":\"" + name + "\", \"type\":" + QString::number(static_cast<int>(type)) + "}";
    JsonHandler aJsonHandler;
    return aJsonHandler.getJsonFromStr(jsonString);
}

TypeE Variable::getType()
{
    return type;
}

