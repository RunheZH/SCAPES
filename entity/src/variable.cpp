#include "../inc/variable.h"
#include "../inc/jsonHandler.h"

Variable::Variable(QString pgmName, QString variableName, TypeE type, int maxSize) : Identifier(pgmName, variableName)
{
    this->type = type;
    this->maxSize = maxSize;
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
    if (type == ARRAY) {
        varObj = JsonHandler::appendToEnd(varObj, JsonHandler::getJsonObj("size", QString::number(maxSize)));
        QJsonObject valueArray = QJsonObject();
        for(int i = 0; i < maxSize; i++) {
            valueArray.insert(QString::number(i), QString::number(false));
        }
        varObj = JsonHandler::appendToEnd(varObj, JsonHandler::getJsonObj("value", valueArray));
    }

    return varObj;
}

void Variable::addToDB()
{
    DBManager db(this->programName);
    db.addVariable(this->getName(), INT);
}

TypeE Variable::getType()
{
    return type;
}

int Variable::getSize()
{
    return maxSize;
}

bool Variable::setValue(int aValue, int position)
{
    if (type != ARRAY && position != 0) {
        return false;
    }
    if (value.size() < position) {
        return false;
    } else if (value.size() == position) {
        value.append(aValue);
    } else {
        value[position] = aValue;
    }

    // pass the new value to the DB
    DBManager db(this->programName);
    db.setVariable(this->getName(),this->getType(),value);

    return true;
}

QVector<int> Variable::getValue()
{

    // get value from the DB
    DBManager db(this->programName);
    QVector<int> varValue = db.getVariableValue(this->getName());

    // set this variable's value as the varValue
    // do we need this ?
    this->value = varValue;

    return varValue;
}

int Variable::getValue(int position)
{   
    // get value from the DB
    DBManager db(this->programName);
    QVector<int> varValue = db.getVariableValue(this->getName());

    // set this variable's value as the varValue
    // do we need this ?
    // if we do, we can call getValue() directly
    this->value = varValue;

    if (value.size() < position) {
        position = value.size() - 1;
    }

    return value[position];
}
