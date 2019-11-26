#include "../inc/label.h"
#include "../inc/jsonHandler.h"

Label::Label(QString pgmName, QString labelName, int stmtLineNum) : Identifier(pgmName, labelName)
{
    this->stmtLineNum = stmtLineNum;
}

Label::~Label(){}

int Label::getLineNum()
{
    return this->stmtLineNum;
}

QJsonObject Label::toJSON()
{
    QJsonObject labelObj = QJsonObject();
    labelObj = JsonHandler::appendToEnd(labelObj, JsonHandler::getJsonObj("stmtLine", QString::number(this->stmtLineNum)));

    return labelObj;
}

void Label::addToDB()
{
    DBManager db(this->programName);
    db.addLabel(this->getName(), this->getLineNum());
}
