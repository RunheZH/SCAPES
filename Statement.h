#ifndef STATEMENT_H_
#define STATEMENT_H_

#include <string>
#include "CommonLib.h"

using namespace std; 

class Statement
{
public:
	virtual ~Statement(){ }
protected:
	virtual ResultState complieStatement(string aStatement);
};

class Read : public Statement
{
public:
	Read();
	static Statement* getInstance();
private:
	ResultState complieStatement(string aStatement) override;
};

class Print : public Statement
{
public:
	Print();
	static Statement* getInstance();
private:
	ResultState complieStatement(string aStatement) override;
};

class DeclInt : public Statement
{
public:
	DeclInt();
	static Statement* getInstance();
private:
	ResultState complieStatement(string aStatement) override;
};

class DeclArr : public Statement
{
public:
	DeclArr();
	static Statement* getInstance();
private:
	ResultState complieStatement(string aStatement) override;
};

class Mov : public Statement
{
public:
	Mov();
	static Statement* getInstance();
private:
	ResultState complieStatement(string aStatement) override;
};

class Add : public Statement
{
public:
	Add();
	static Statement* getInstance();
private:
	ResultState complieStatement(string aStatement) override;
};

class Comp : public Statement
{
public:
	Comp();
	static Statement* getInstance();
private:
	ResultState complieStatement(string aStatement) override;
};

class JLess : public Statement
{
public:
	JLess();
	static Statement* getInstance();
private:
	ResultState complieStatement(string aStatement) override;
};

class JMore : public Statement
{
public:
	JMore();
	static Statement* getInstance();
private:
	ResultState complieStatement(string aStatement) override;
};

class JEq : public Statement
{
{
public:
	JEq();
	static Statement* getInstance();
private:
	ResultState complieStatement(string aStatement) override;
};

class Jump : public Statement
{
public:
	Jump();
	static Statement* getInstance();
private:
	ResultState complieStatement(string aStatement) override;
};

class End : public Statement
{
public:
	End();
	static Statement* getInstance();
private:
	ResultState complieStatement(string aStatement) override;
};

#endif

