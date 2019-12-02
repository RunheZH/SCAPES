#include "../inc/statement.h"

Statement::Statement(QString programName, QString statement, QMap<QString, std::shared_ptr<Identifier>>& ids, int lineNum) : ids(ids)
{
    this->programName = programName;
    this->statement = statement;
    //this->ids = ids;
    this->lineNum = lineNum;
    this->label = nullptr;
    QStringList args = statement.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if (args[0].endsWith(":")){
        //qDebug() << "RUNHE: detected label";
        this->label = new Label(this->programName, args[0].left(args[0].lastIndexOf(":")), lineNum);
        ids.insert(this->label->getName(), std::shared_ptr<Label>(this->label));
        JsonHandler jsonHdlr(this->programName);
        jsonHdlr.addElement(LABEL, label->getName(), label->toJSON());
        // get rid of the leading spaces
        this->statement = statement.mid(args[0].length() + 1);
    }
}

Statement::~Statement(){}

ResultState Statement::checkOperand(QString &Qop, Operand& op)
{
    bool literal;
    int opValue = Qop.toInt(&literal);
    if (literal) {
        op.setValue(opValue);
        return All_LITERAL;
    }
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
    op.setIdentifier(jsonHdlr.findVariable(operand));

    if(op.getIdentifier() == nullptr){
        return VARIABLE_ONE_NOT_FOUND_ERROR;
    } else if (indexOne != -1) {
        if (static_cast<Variable*>(op.getIdentifier())->getType() != TypeE::ARRAY) {
            return VARIABLE_NOT_FOUND_ERROR;
        } else {
            op.setIndex(indexOne);
            return jsonHdlr.findInitArrayValue(operand, indexOne);
        }

    } else {
        if (static_cast<Variable*>(op.getIdentifier())->getType() != TypeE::INT) {
            return VARIABLE_NOT_FOUND_ERROR;
        } else {
            return jsonHdlr.findInitIntValue(operand);
        }
    }
}

ResultState Statement::checkTwoOperand(QString &Qop1, Operand& op1, QString &Qop2, Operand& op2, bool notAllowed, bool checkInit)
{
    TypeE type1 = UNDEFINED;
    TypeE type2 = UNDEFINED;
    bool literal1;
    bool literal2;
    int op1Value = Qop1.toInt(&literal1);
    int op2Value = Qop2.toInt(&literal2);
    if (literal1 && literal2 && !notAllowed) {
        op1.setValue(op1Value);
        op2.setValue(op2Value);
        return All_LITERAL;
    } else if (literal2 && notAllowed) {
        return INVALID_OPERAND;
    } else if (literal1) {
        op1.setValue(op1Value);
        type1 = LITERAL;
    } else if (literal2) {
        op2.setValue(op2Value);
        type2 = LITERAL;
    }

    ResultState resultState1 = NO_ERROR;
    ResultState resultState2 = NO_ERROR;

    QString operand1 = Qop1;
    int indexOne1 = operand1.indexOf("[");
    int indexTwo1 = operand1.indexOf("]");
    QString operand2 = Qop2;
    int indexOne2 = operand2.indexOf("[");
    int indexTwo2 = operand2.indexOf("]");
    JsonHandler jsonHdlr(this->programName);
    if (type1 != LITERAL && indexOne1 != -1) {
        bool ok;
        int position = operand1.mid(indexOne1+1, (indexTwo1 - indexOne1 - 1)).toInt(&ok);
        if (!ok) {
          resultState1 = VARIABLE_ONE_NOT_FOUND_ERROR;
        } else {
            operand1 = operand1.mid(0, indexOne1);
            indexOne1 = position;
            type1 = ARRAY;
        }
    }
    if (type2 != LITERAL && indexOne2 != -1) {
        bool ok;
        int position = operand2.mid(indexOne2+1, (indexTwo2 - indexOne2 - 1)).toInt(&ok);
        if (!ok) {
          resultState2 = VARIABLE_TWO_NOT_FOUND_ERROR;
        } else {
            operand2 = operand2.mid(0, indexOne2);
            indexOne2 = position;
            type2 = ARRAY;
        }
    }

    op1.setIdentifier(jsonHdlr.findVariable(operand1));
    op2.setIdentifier(jsonHdlr.findVariable(operand2));


    if (type1 == LITERAL) {
        type1 = INT;
    } else if(op1.getIdentifier() == nullptr){
        resultState1 = VARIABLE_NOT_FOUND_ERROR;
    } else if (indexOne1 != -1) {
        if (static_cast<Variable*>(op1.getIdentifier())->getType() != TypeE::ARRAY) {
            resultState1 =  VARIABLE_NOT_FOUND_ERROR;
        } else {
            op1.setIndex(indexOne1);
            resultState1 = jsonHdlr.findInitArrayValue(operand1, indexOne1);
            type1 = INT;
        }
    } else {
        if (static_cast<Variable*>(op1.getIdentifier())->getType() == TypeE::INT) {
            resultState1 = jsonHdlr.findInitIntValue(operand1);
            type1 = INT;
        } else if (static_cast<Variable*>(op1.getIdentifier())->getType() == TypeE::ARRAY) {
            type1 = ARRAY;
        } else {
            resultState1 = VARIABLE_NOT_FOUND_ERROR;
        }
    }

    if (type2 == LITERAL) {
        type2 = INT;
    } else if(op2.getIdentifier() == nullptr){
        resultState2 = VARIABLE_NOT_FOUND_ERROR;
    } else if (indexOne2 != -1) {
        if (static_cast<Variable*>(op2.getIdentifier())->getType() != TypeE::ARRAY) {
            resultState2 =  VARIABLE_NOT_FOUND_ERROR;
        } else {
            op2.setIndex(indexOne2);
            if (checkInit) {
                resultState2 = jsonHdlr.findInitArrayValue(operand2, indexOne2);
            } else if (indexOne2 >= static_cast<Variable*>(op2.getIdentifier())->getSize()) {
                resultState2 =  VARIABLE_NOT_FOUND_ERROR;
            } else {
                jsonHdlr.initArrayValue(operand2, indexOne2);
            }
            type2 = INT;
        }
    } else {
        if (static_cast<Variable*>(op2.getIdentifier())->getType() == TypeE::INT) {
            if (checkInit) {
                resultState2 = jsonHdlr.findInitIntValue(operand2);
            } else {
                jsonHdlr.initIntValue(operand2);
            }
            type2 = INT;
        } else if (static_cast<Variable*>(op2.getIdentifier())->getType() == TypeE::ARRAY) {
            type2 = ARRAY;
        } else {
            resultState2 = VARIABLE_NOT_FOUND_ERROR;
        }
    }

    ResultState finalResultState = getResultStateForTwo(resultState1, resultState2);
    if (finalResultState == NO_ERROR && type1 != type2) {
        return DIFF_TYPE_ERROR;
    } else {
        return finalResultState;
    }
}

ResultState Statement::getResultStateForTwo(ResultState resultState1, ResultState resultState2)
{
    if (resultState1 == VARIABLE_NOT_FOUND_ERROR && resultState2 == NO_ERROR) {
        return VARIABLE_ONE_NOT_FOUND_ERROR;
    } else if (resultState1 == NO_ERROR && resultState2 == VARIABLE_NOT_FOUND_ERROR) {
        return VARIABLE_TWO_NOT_FOUND_ERROR;
    } else if (resultState1 == VARIABLE_NOT_FOUND_ERROR && resultState2 == VARIABLE_NOT_FOUND_ERROR) {
        return VARIABLE_ONE_AND_TWO_NOT_FOUND_ERROR;
    } else if (resultState1 == VARIABLE_NOT_INIT_ERROR && resultState2 == NO_ERROR) {
        return VARIABLE_ONE_NOT_INIT_ERROR;
    } else if (resultState1 == NO_ERROR && resultState2 == VARIABLE_NOT_INIT_ERROR) {
        return VARIABLE_TWO_NOT_INIT_ERROR;
    } else if (resultState1 == VARIABLE_NOT_INIT_ERROR && resultState2 == VARIABLE_NOT_INIT_ERROR) {
        return VARIABLE_ONE_AND_TWO_NOT_INIT_ERROR;
    } else if (resultState1 == VARIABLE_NOT_INIT_ERROR && resultState2 == VARIABLE_NOT_FOUND_ERROR) {
        return VARIABLE_ONE_NOT_INIT_AND_TWO_NOT_FOUND_ERROR;
    } else if (resultState1 == VARIABLE_NOT_FOUND_ERROR && resultState2 == VARIABLE_NOT_INIT_ERROR) {
        return VARIABLE_ONE_NOT_FOUND_AND_TWO_NOT_INIT_ERROR;
    } else {
        return NO_ERROR;
    }
}
