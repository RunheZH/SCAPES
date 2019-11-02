#ifndef STATEMENT_H
#define STATEMENT_H

#include "common_lib.h"
#include "operand.h"
#include "label.h"

class Statement
{
public:
	Statement(string programName, string statement);
	virtual ~Statement();
	virtual ResultState complie(string aStatement) = 0;
	virtual ResultState run(string aStatement) = 0;

protected:
	string programName;
	string statement;
	Operand operands[2];
	Label  label;
};

#endif