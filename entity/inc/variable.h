#ifndef VARIABLE_H
#define VARIABLE_H

#include "common_lib.h"
#include "identifier.h"

class Variable : public Identifier
{
public:
    Variable(QString programName, QString variableName, TypeE variableType, int maxSize = 0);
    ~Variable();
    QJsonObject toJSON();
    void addToDB();
    TypeE getType();
    int getSize();
    //it will change the value if the user provide the vaild index
    bool setValue(int aValue, int position = 0);
    QVector<int> getValue();
    //it will return the last value if position bigger than size
    int getValue(int position);

private:
    TypeE type;
    int maxSize;
    QVector<int> value;
};

#endif
