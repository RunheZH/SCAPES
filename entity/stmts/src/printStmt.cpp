#include "../inc/printStmt.h"

PrintStmt::PrintStmt(QString pgmName, QString stmt, QMap<QString, std::shared_ptr<Identifier>>& idsLib, int lnNum) : Statement(pgmName, stmt, idsLib, lnNum)
{
    qDebug() << "PrintStmt()";
}

PrintStmt::~PrintStmt()
{
    delete (op1.getIdentifier());
    qDebug() << "~PrintStmt()";
}

ResultState PrintStmt::compile()
{
    qDebug() << "PrintStmt.compile()";

    JsonHandler jsonHdlr(this->programName);
    QStringList args = this->statement.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if (args.size() != 2){
        if(args.size() == 1){
            return NO_OPERAND_ONE_ERROR;
        }
    }

    QString instruction = args[0];instruction = args[0];
    QString operand1 = args[1];
    ResultState aResulsState = checkOperand(operand1, op1);
    QJsonObject op1Obj;
    if (aResulsState != ResultState::NO_ERROR && aResulsState !=NO_ERROR) {
        for (int i = 2; i < args.size(); i++) {
            operand1 = " " + args[i];
        }
        op1Obj = JsonHandler::getJsonObj(OP_1, operand1);
    } else {
        op1Obj = JsonHandler::getJsonObj(OP_1, op1.getIdentifier()->getName());
    }
    QJsonObject stmtObj = JsonHandler::getJsonObj(instruction, op1Obj);
    jsonHdlr.addElement(STMT, QString::number(lineNum), stmtObj);

    return NO_ERROR;
}

ReturnValue* PrintStmt::run()
{
    qDebug() << "PrintStmt.run()";

    // Variable aVariable = DBM.getVariable(op1->getIdentifier()->getName());
    // OR
    // Variable* aVariable = static_cast<Variable*>(op1->getIdentifier());
    // QString printedValue = aVariable->getValue();
    // qDebug() << printedValue;

    Variable* aVariable = static_cast<Variable*>(op1.getIdentifier());
    if (aVariable->getValue().isEmpty())
        return new ReturnValue(VARIABLE_NOT_FOUND_ERROR);

    QVector<int> aVector = aVariable->getValue();

    // if we read value from the INT type
    if (aVector.size() == 1){
        qDebug() << "the value of this int is:";
        qDebug() << aVariable->getValue(aVector[0]);
    }
    // if we read value from the ARRAY type
    else if (aVector.size() > 1){
        qDebug() << "the value of this array is:";
        for (int i=0; i<aVector.size(); i++){
            qDebug() << aVariable->getValue(aVector[i]);
        }
    }
    else{
        qDebug() << "ERROR";
    }


    return new ReturnValue(NO_ERROR, NO_JUMP, NO_CMP);
}
