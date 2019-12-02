#include "../inc/readStmt.h"

ReadStmt::ReadStmt(QString pgmName, QString stmt, QMap<QString, std::shared_ptr<Identifier>>& idsLib, int lnNum) : Statement(pgmName, stmt, idsLib, lnNum)
{
    qDebug() << "ReadStmt()";
}

ReadStmt::~ReadStmt()
{
    delete (op1.getIdentifier());
    qDebug() << "~ReadStmt()";
}

ResultState ReadStmt::compile()
{
    qDebug() << "ReadStmt.compile()";
    QStringList args = this->statement.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if (args.size() != 2){ // syntax checking
        if(args.size() == 1){
            return NO_OPERAND_ONE_ERROR;
        }
        else {
            return OPERAND_NUMBER_EXCEED_ERROR;
        }
    }

    QString instruction = args[0];
    QString operand1 = args[1];
    QRegExp pattern("\\[[0-9]+\\]");
    if (operand1.contains(pattern)) // an array element, access using negative indices are not supported
    {
        // found variable and index
        QStringList op1_args = operand1.split(QRegExp("[\\[\\]]"), QString::SkipEmptyParts);
        QMap<QString, std::shared_ptr<Identifier>>::iterator foundVar_it = ids.find(op1_args[0]);
        if (foundVar_it != ids.end() && dynamic_cast<Variable*>(foundVar_it.value().get())) // found variable
        {
            if (dynamic_cast<Variable*>(foundVar_it.value().get())->getType() != ARRAY)
                return DIFF_TYPE_ERROR;

            if (op1_args[1] > dynamic_cast<Variable*>(foundVar_it.value().get())->getValue().size())
                return INDEX_OUT_OF_BOUNDS;

            op1.setIdentifier(foundVar_it.value().get());
            op1.setIndex(op1_args[1].toInt());

        }
        else
            return VARIABLE_NOT_FOUND_ERROR;
    }
    else
    {
        if (ids.find(operand1) == ids.end())
            return VARIABLE_NOT_FOUND_ERROR;

        if (dynamic_cast<Variable*>(ids.find(operand1).value().get())->getType() != INT)
            return DIFF_TYPE_ERROR;

        op1.setIdentifier(ids.find(operand1).value().get());
    }
    // set "initialized?" to true in JSON
    JsonHandler jsonHdlr(this->programName);
    if (dynamic_cast<Variable*>(op1.getIdentifier())->getType() == INT)
        jsonHdlr.initIntValue(op1.getIdentifier()->getName());
    else // array
        jsonHdlr.initArrayValue(op1.getIdentifier()->getName(), op1.getIndex());

    // add to JSON
    QJsonObject op1Obj = JsonHandler::getJsonObj(OP_1, operand1);
    QJsonObject stmtObj = JsonHandler::getJsonObj(instruction, op1Obj);
    jsonHdlr.addElement(STMT, QString::number(lineNum), stmtObj);

    return NO_ERROR;
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
        aVariable->setValue(newValue, 0);
    }
    // if we set value to an arryr
    else if (variableType == TypeE::ARRAY){
        // for loop to set value to every vector?
        aVariable->setValue(newValue, 0);
    }
    else{
        qDebug() << "ERROR";
    }

    return new ReturnValue(NO_ERROR, NO_JUMP, NO_CMP);
}
