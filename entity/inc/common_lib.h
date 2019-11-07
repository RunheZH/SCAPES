#ifndef COMMON_LIB_H
#define COMMON_LIB_H

#include <QtDebug>
#include <QString>
#include <QStringList>
#include <QRegExp>
#define MAX_VALUE_16 32767

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
    INVALID_STATEMENT
};

enum TypeE
{
	INT,
	ARRAY
};

#endif

