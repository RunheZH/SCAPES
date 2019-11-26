#ifndef COMMON_LIB_H
#define COMMON_LIB_H

#include <QApplication>
#include <QFile>
#include <QtDebug>
#include <QString>
#include <QStringList>
#include <QRegExp>

#define MAX_VALUE_16 32767
#define STMT  "statement"
#define VAR   "variable"
#define LABEL "label"
#define OP_1  "op_1"
#define OP_2  "op_2"
#define END   "end"
#define NO_JUMP -1
#define NO_CMP  -2

enum StatementId
{
    ADD_STMT,
    CMP_STMT,
    DCA_STMT,
    DCI_STMT,
    END_STMT,
    JEQ_STMT,
    JLS_STMT,
    JMR_STMT,
    JMP_STMT,
    MOV_STMT,
    PRT_STMT,
    RDI_STMT,
    INVALID_STMT
};

enum ResultState
{
    NO_ERROR,
    All_LITERAL,
    DIFF_TYPE_ERROR,
    FILE_OPEN_ERROR,
    INVALID_STATEMENT,
    INVALID_OPERAND,
    NO_OPERAND_ONE_ERROR,
    NO_OPERAND_TWO_ERROR,
    OPERAND_NUMBER_EXCEED_ERROR,
    VARIABLE_NOT_FOUND_ERROR,
    VARIABLE_ONE_NOT_FOUND_ERROR,
    VARIABLE_TWO_NOT_FOUND_ERROR,
    VARIABLE_ONE_AND_TWO_NOT_FOUND_ERROR,
    VARIABLE_NOT_INIT_ERROR,
    VARIABLE_ONE_NOT_INIT_ERROR,
    VARIABLE_TWO_NOT_INIT_ERROR,
    VARIABLE_ONE_AND_TWO_NOT_INIT_ERROR,
    VARIABLE_ONE_NOT_FOUND_AND_TWO_NOT_INIT_ERROR,
    VARIABLE_ONE_NOT_INIT_AND_TWO_NOT_FOUND_ERROR,
    LABEL_NOT_FOUND_ERROR,
    COMPILATION_ERROR,
    RUNTIME_ERROR,
    NO_END
};

enum TypeE
{
    UNDEFINED,
    LITERAL,
    INT,
    ARRAY
};

class ReturnValue
{
public:
    ReturnValue(ResultState result, qint16 jumpTo=NO_JUMP, qint16 compareR=NO_CMP) : error(result), jumpToLine(jumpTo), compareResult(compareR){}
    ~ReturnValue(){}
    ResultState getResultState(){return this->error;}
    qint16 getJumpToLine(){return this->jumpToLine;}
    qint16 getCompareResult(){return this->compareResult;}

private:
    ResultState error;
    qint16 jumpToLine;
    qint16 compareResult;
};

#endif

