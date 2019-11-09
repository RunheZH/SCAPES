#include "../inc/label.h"
#include "../inc/jsonHandler.h"

Label::Label(QString labelName) : Identifier(labelName){}

Label::~Label(){}

QJsonObject Label::toJSON()
{
    QString jsonString = "{\"name\":\"" + name + "\"}";
    JsonHandler aJsonHandler;
    return aJsonHandler.getJsonFromStr(jsonString);
}
