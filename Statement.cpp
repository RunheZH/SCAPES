#include "Statement.h"

static Logger* m_logger = Logger::getInstance("statement");

//Class Read
static Statement* Read::getInstance()
{
	static Read s_instance;
	return &s_instance;
}

ResultState Read::complieStatement(string aStatement){
{

	return ResultState::NO_ERROR;
}

//Class Print
static Statement* Print::getInstance()
{
	static Print s_instance;
	return &s_instance;
}

ResultState Print::complieStatement(string aStatement){
{

	return ResultState::NO_ERROR;
}

//Class DeclInt
static Statement* DeclInt::getInstance()
{
	static DeclInt s_instance;
	return &s_instance;
}

ResultState DeclInt::complieStatement(string aStatement){
{

	return ResultState::NO_ERROR;
}

//Class DeclArr
static Statement* DeclArr::getInstance()
{
	static DeclArr s_instance;
	return &s_instance;
}

ResultState DeclArr::complieStatement(string aStatement){
{

	return ResultState::NO_ERROR;
}

//Class Mov
static Statement* Mov::getInstance()
{
	static Mov s_instance;
	return &s_instance;
}

ResultState Mov::complieStatement(string aStatement){
{

	return ResultState::NO_ERROR;
}

//Class Add
static Statement* Add::getInstance()
{
	static Add s_instance;
	return &s_instance;
}

ResultState Add::complieStatement(string aStatement){
{

	return ResultState::NO_ERROR;
}

//Class Comp
static Statement* Comp::getInstance()
{
	static Comp s_instance;
	return &s_instance;
}

ResultState Comp::complieStatement(string aStatement){
{

	return ResultState::NO_ERROR;
}

//Class JLess
static Statement* JLess::getInstance()
{
	static JLess s_instance;
	return &s_instance;
}

ResultState JLess::complieStatement(string aStatement){
{

	return ResultState::NO_ERROR;
}

//Class JMore
static Statement* JMore::getInstance()
{
	static JMore s_instance;
	return &s_instance;
}

ResultState JMore::complieStatement(string aStatement){
{

	return ResultState::NO_ERROR;
}

//Class JEq
static Statement* JEq::getInstance()
{
	static JEq s_instance;
	return &s_instance;
}

ResultState JEq::complieStatement(string aStatement){
{

	return ResultState::NO_ERROR;
}

//Class Jump
static Statement* Jump::getInstance()
{
	static Jump s_instance;
	return &s_instance;
}

ResultState Jump::complieStatement(string aStatement){
{

	return ResultState::NO_ERROR;
}

//Class End
static Statement* End::getInstance()
{
	static End s_instance;
	return &s_instance;
}

ResultState End::complieStatement(string aStatement){
{

	return ResultState::NO_ERROR;
}
