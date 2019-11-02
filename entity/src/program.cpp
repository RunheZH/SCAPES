#include "../inc/program.h"

Program::Program(string programName, string pgmScript)
{
	this->programName = programName;
	this->pgmScript = pgmScript;
	/*
	m_statementMap.insert(std::make_pair(StatementId::READ_STMT, Read::getInstance()));
	m_statementMap.insert(std::make_pair(StatementId::PRINT_STMT, Print::getInstance()));
	m_statementMap.insert(std::make_pair(StatementId::DECLINT_STMT, DeclInt::getInstance()));
	m_statementMap.insert(std::make_pair(StatementId::DECLARR_STMT, DeclArr::getInstance()));
	m_statementMap.insert(std::make_pair(StatementId::MOV_STMT, Mov::getInstance()));
	m_statementMap.insert(std::make_pair(StatementId::ADD_STMT, Add::getInstance()));
	m_statementMap.insert(std::make_pair(StatementId::COMP_STMT, Comp::getInstance()));
	m_statementMap.insert(std::make_pair(StatementId::JLESS_STMT, JLess::getInstance()));
	m_statementMap.insert(std::make_pair(StatementId::JMORE_STMT, JMore::getInstance()));
	m_statementMap.insert(std::make_pair(StatementId::JEQ_STMT, JEq::getInstance()));
	m_statementMap.insert(std::make_pair(StatementId::JUMP_STMT, Jump::getInstance()));
	m_statementMap.insert(std::make_pair(StatementId::END_STMT, End::getInstance()));
	*/
}

ResultState Program::save()
{
}

ResultState Program::compile()
{
	/*
	ResultState aResultState;
	for(;;){
		aStatementId = ;
		aResultState = compileSingle(aStatementId, aStatement);
		if (aResultState != ResultState::NO_ERROR)
			return aResultState;		
	}
	return aResultState;
	*/
}

ResultState Program::run()
{
}

/*
ResultState Program::compileSingle(StatementId stmtID, string aStmt)
{
    auto it = find_if (programDatas.begin (), programDatas.end (),
        [aStatementId] (const std::map<StatementId, Statement*> &element) { return element.first == aStatementId;});
    if (it != programDatas.end ()) {
        return (*it).second->complieStatement;
	}
 
	return 0;
}*/
