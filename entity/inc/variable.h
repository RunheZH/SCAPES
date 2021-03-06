#ifndef VARIABLE_H
#define VARIABLE_H

#include "common_lib.h"
#include "identifier.h"

class Variable : public Identifier
{
public:
    Variable(QString programName, QString variableName, TypeE variableType, int maxSize = 1);
    ~Variable();
    QJsonObject toJSON();
    TypeE getType();
    int getSize();
    int getUsedSize();
    void setSize(int newSize);
    void setUsedSize(int newUsedSize);
    //it will change the value if the user provide the vaild index
    bool setValue(int aValue, int position = 0);
    QVector<int> getValue();
    //it will return the last value if position bigger than size
    int getValue(int position);

private:
    TypeE type;
    int maxSize;
    int usedSize;
    QVector<int> value;
};

#endif
