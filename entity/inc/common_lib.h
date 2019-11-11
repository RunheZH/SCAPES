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
    FILE_OPEN_ERROR,
    INVALID_STATEMENT,
    NO_OPERAND_ONE_ERROR,
    NO_OPERAND_TWO_ERROR,
    OPERAND_NUMBER_EXCEED_ERROR,
    VARIABLE_ONE_NOT_FOUND_ERROR,
    VARIABLE_TWO_NOT_FOUND_ERROR,
    VARIABLE_ONE_AND_TWO_NOT_FOUND_ERROR
};

enum TypeE
{
    INT,
    ARRAY
};

#endif

