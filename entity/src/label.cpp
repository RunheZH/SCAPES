#include "../inc/label.h"
#include "../inc/jsonHandler.h"

Label::Label(QString labelName, qint16 stmtLineNum) : Identifier(labelName)
{
    this->stmtLineNum = stmtLineNum;
}

Label::~Label(){}

QJsonObject Label::toJSON()
{
    JsonHandler jsonHdlr;
    QJsonObject labelObj = QJsonObject();
    labelObj = jsonHdlr.appendToEnd(labelObj, jsonHdlr.getJsonObj("stmtLine", QString::number(this->stmtLineNum)));

    return labelObj;
}
