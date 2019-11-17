#ifndef STATEMENT_H
#define STATEMENT_H

#include "common_lib.h"
#include "operand.h"
#include "label.h"
#include "jsonHandler.h"
#include "variable.h"


class Statement
{
public:
    Statement(QString programName, QString statement, Label* label, qint16 lineNum);
	virtual ~Statement();
    virtual ResultState compile() = 0;
    virtual ResultState run() = 0;
    virtual qint16 getLineNum() {return this->lineNum;}
    virtual ResultState checkOperand(QString &Qop, Operand* op){
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
                return jsonHdlr.findInitValue(operand, indexOne);
            }

        } else {
            if (static_cast<Variable*>(op->getIdentifier())->getType() != TypeE::INT) {
                return VARIABLE_NOT_FOUND_ERROR;
            } else {
                return jsonHdlr.findInitValue(operand, 0);
            }
        }
    }

protected:
    QString programName;
    QString statement;
    Label*  label;
    qint16  lineNum;
};

#endif
