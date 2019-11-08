#include "../inc/label.h"
#include "../inc/jsonHandler.h"

QJsonObject Label::toJSon()
{
    QString jsonString = "{\"name\":\"" + name + "\"}";
    JsonHandler aJsonHandler;
    return aJsonHandler.getJsonFromStr(jsonString);
}
