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
    NOT_INTEGER_ERROR,
    DIFF_TYPE_ERROR,
    FILE_OPEN_ERROR,
    INDEX_OUT_OF_BOUNDS,
    INVALID_STATEMENT,
    INVALID_OPERAND,
    NO_OPERAND_ONE_ERROR,
    NO_OPERAND_TWO_ERROR,
    NO_OPERAND_ONE_AND_TWO_ERROR,
    OPERAND_NUMBER_EXCEED_ERROR,
    EXPECT_INT_OR_ARR_ELM_ERROR,
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
    REDECLARE_VAR_ERROR,
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
    ReturnValue(ResultState result, int jumpTo=NO_JUMP, int compareR=NO_CMP) : error(result), jumpToLine(jumpTo), compareResult(compareR){}
    ~ReturnValue(){}
    ResultState getResultState(){return this->error;}
    int getJumpToLine(){return this->jumpToLine;}
    int getCompareResult(){return this->compareResult;}

private:
    ResultState error;
    int jumpToLine;
    int compareResult;
};

#endif

