#include "../inc/variable.h"
#include "../inc/jsonHandler.h"

QJsonObject Variable::toJSon()
{
    QString jsonString = "{\"name\":\"" + name + "\", \"type\":" + QString::number(static_cast<int>(type)) + "}";
    JsonHandler aJsonHandler;
    return aJsonHandler.getJsonFromStr(jsonString);
}

