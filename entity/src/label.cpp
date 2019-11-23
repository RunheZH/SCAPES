#include "../inc/label.h"
#include "../inc/jsonHandler.h"

Label::Label(QString labelName, int stmtLineNum) : Identifier(labelName)
{
    this->stmtLineNum = stmtLineNum;
}

Label::~Label(){}

QJsonObject Label::toJSON()
{
    QJsonObject labelObj = QJsonObject();
    labelObj = JsonHandler::appendToEnd(labelObj, JsonHandler::getJsonObj("stmtLine", QString::number(this->stmtLineNum)));

    return labelObj;
}
