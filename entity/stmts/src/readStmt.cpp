#include "../inc/readStmt.h"

ReadStmt::ReadStmt(QString pgmName, QString stmt, Label* lbl, qint16 lnNum) : Statement(pgmName, stmt, lbl, lnNum)
{
    qDebug() << "ReadStmt()";
}

ReadStmt::~ReadStmt()
{
    delete (&op1);
    qDebug() << "~ReadStmt()";
}

ResultState ReadStmt::compile()
{
    qDebug() << "ReadStmt.compile()";
    QStringList args = this->statement.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if (args.size() != 2){
        if(args.size() == 1){
            return NO_OPERAND_ONE_ERROR;
        }
        else {
            return OPERAND_NUMBER_EXCEED_ERROR;
        }
    }

    QString instruction = args[0];
    QString operand1 = args[1];
    JsonHandler jsonHdlr(this->programName);
    ResultState aResulsState = checkOperand(operand1, op1);
    if (aResulsState != ResultState::NO_ERROR) {
        return aResulsState;
    }

    QJsonObject op1Obj = JsonHandler::getJsonObj(OP_1, operand1);
    QJsonObject stmtObj = JsonHandler::getJsonObj(instruction, op1Obj);
    jsonHdlr.addElement(STMT, QString::number(lineNum), stmtObj);

    if (label)
    {
        jsonHdlr.addElement(LABEL, label->getName(), label->toJSON());
    }
    return NO_ERROR;
}

ResultState ReadStmt::checkOperand(QString &operand, Operand& op){
    int indexOne = operand.indexOf("[");
    int indexTwo = operand.indexOf("]");
    JsonHandler jsonHdlr(this->programName);
    if (indexOne != -1 && indexTwo > indexOne) {
        bool ok;
        int position = operand.mid(indexOne+1, (indexTwo - indexOne - 1)).toInt(&ok);
        if (!ok) {
          return VARIABLE_ONE_NOT_FOUND_ERROR;
        }
        operand = operand.mid(0, indexOne);
        indexOne = position;
    }
        op.setIdentifier(jsonHdlr.findVariable(operand));

    // Variable 1 not found
    if(op.getIdentifier() == nullptr){
        return VARIABLE_ONE_NOT_FOUND_ERROR;
    } else if (indexOne != -1) {
        if (static_cast<Variable*>(op.getIdentifier())->getType() != TypeE::ARRAY) {
            return VARIABLE_ONE_NOT_FOUND_ERROR;
        } else {
           op.setIndex(indexOne);
           return jsonHdlr.initArrayValue(operand, indexOne);
        }

    } else {
        if (static_cast<Variable*>(op.getIdentifier())->getType() != TypeE::INT) {
            return VARIABLE_ONE_NOT_FOUND_ERROR;
        } else {
           return jsonHdlr.initIntValue(operand);
        }
    }
}

ReturnValue* ReadStmt::run()
{
    qDebug() << "ReadStmt.run()";

    // Variable aVariable = DBM.getVariable(op1->getIdentifier()->getName());
    // Value newValue = UI.popRead(); OR Value newValue = controller.readValue();
    // aVariable.setValue(newValue);
    // DBM.setVariable(aVariable.getName(), aVariable.getType(), newValue);


    Variable* aVariable = static_cast<Variable*>(op1.getIdentifier());
    TypeE variableType = aVariable->getType();

    int newValue = 0;
    // TODO: include UI
    //newValue = UI.popRead();

    // if we set value to a int
    if (variableType == TypeE::INT){
        aVariable->setValue(newValue,0);
    }
    // if we set value to an arryr
    else if (variableType == TypeE::ARRAY){
        // for loop to set value to every vector?
        aVariable->setValue(newValue,0);
    }
    else{
        qDebug() << "ERROR";
    }



    return new ReturnValue(NO_ERROR, NO_JUMP, NO_CMP);
}
