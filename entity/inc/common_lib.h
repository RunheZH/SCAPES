#ifndef COMMON_LIB_H
#define COMMON_LIB_H

#include <QtDebug>
#include <QString>
#include <QStringList>
#include <QRegExp>

enum StatementId
{
	READ_STMT,
	PRINT_STMT,
	DECLINT_STMT,
	DECLARR_STMT,
	MOV_STMT,
	ADD_STMT,
	COMP_STMT,
	JLESS_STMT,
	JMORE_STMT,
	JEQ_STMT,
	JUMP_STMT,
	END_STMT
};

enum ResultState
{
    NO_ERROR,
    FILE_OPEN_ERROR
};

enum TypeE
{
	INT,
	ARRAY
};

#endif

