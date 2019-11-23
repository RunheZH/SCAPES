#include "../inc/statement.h"

//static Logger* m_logger = Logger::getInstance("statement");

Statement::Statement(QString programName, QString statement, Label* label, qint16 lineNum)
{
    this->programName = programName;
    this->statement = statement;
    this->label = label;
    this->lineNum = lineNum;
}

ResultState Statement::checkOperand(QString &Qop, Operand* op){
        QString operand = Qop;
        int indexOne = operand.indexOf("[");
        int indexTwo = operand.indexOf("]");
        JsonHandler jsonHdlr(this->programName);
        if (indexOne != -1) {
            bool ok;
            int position = operand.mid(indexOne+1, (indexTwo - indexOne - 1)).toInt(&ok);
            if (!ok) {
              return VARIABLE_ONE_NOT_FOUND_ERROR;
            }
            operand = operand.mid(0, indexOne);
            indexOne = position;
        }
           op = new Operand(jsonHdlr.findVariable(operand));

        // Variable 1 not found
        if(op->getIdentifier() == nullptr){
            return VARIABLE_ONE_NOT_FOUND_ERROR;
        } else if (indexOne != -1) {
            if (static_cast<Variable*>(op->getIdentifier())->getType() != TypeE::ARRAY) {
                return VARIABLE_NOT_FOUND_ERROR;
            } else {
                return jsonHdlr.findInitArrayValue(operand, indexOne);
            }

        } else {
            if (static_cast<Variable*>(op->getIdentifier())->getType() != TypeE::INT) {
                return VARIABLE_NOT_FOUND_ERROR;
            } else {
                return jsonHdlr.findInitIntValue(operand);
            }
        }
    }

Statement::~Statement()
{}
