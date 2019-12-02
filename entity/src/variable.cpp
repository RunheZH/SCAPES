#include "../inc/variable.h"
#include "../inc/jsonHandler.h"

Variable::Variable(QString pgmName, QString variableName, TypeE type, int maxSize) : Identifier(pgmName, variableName)
{
    this->type = type;
    this->maxSize = maxSize;
    this->usedSize = 0;
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
        varObj = JsonHandler::appendToEnd(varObj, JsonHandler::getJsonObj("initialized?", valueArray));
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

int Variable::getUsedSize()
{
    return usedSize;
}

void Variable::setUsedSize(int newUsedSize)
{
    usedSize = newUsedSize;
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
    //DBManager db(this->programName);
    // NOTE : not sure if we need DB after restructure
    //QVector<int> varValue = db.getVariableValue(this->getName());

    // set this variable's value as the varValue
    // do we need this ?
    //this->value = varValue;
  
    /*QString aValue;
    if (value.size()==0) {
        aValue = "undefined";
    } else if (value.size()==1) {
        aValue = QString::number(value[0]);
    } else {
        aValue += "[" + QString::number(value[0]);
        for(int i = 1; i < value.size(); ++i) {
            aValue += ", " + QString::number(value[i]);
        }
        aValue += "]";
    }
    return aValue;*/
    return value;
}

QString Variable::getValue(int position)
{
    // NOTE : not sure if we need DB after restructure
    // get value from the DB
    //DBManager db(this->programName);
    //QVector<int> varValue = db.getVariableValue(this->getName());

    // set this variable's value as the varValue
    // do we need this ?
    // if we do, we can call getValue() directly
    //this->value = varValue;
    if (value.size() < position) {
        return "undefined";
    }

    return QString::number(value[position]);
}
