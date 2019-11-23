#ifndef VARIABLE_H
#define VARIABLE_H

#include "common_lib.h"
#include "identifier.h"

class Variable : public Identifier
{
public:
    Variable(QString variableName, TypeE variableType);
    ~Variable();
    QJsonObject toJSON();
    TypeE getType();
    //it will change the value if the user provide the invaild index
    bool changeValue(int aValue, int position = 0);
    QVector<int> getValue();
    //it will return the last value if position bigger than size
    int getValue(int position);

private:
    TypeE type;
    QVector<int> value;
};

#endif
