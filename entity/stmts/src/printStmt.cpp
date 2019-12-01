#include "../inc/printStmt.h"

PrintStmt::PrintStmt(QString pgmName, QString stmt, Label* lbl, qint16 lnNum) : Statement(pgmName, stmt, lbl, lnNum)
{
    qDebug() << "PrintStmt()";
}

PrintStmt::~PrintStmt()
{
    delete (op1);
    qDebug() << "~PrintStmt()";
}

ResultState PrintStmt::compile()
{
    qDebug() << "PrintStmt.compile()";

    JsonHandler jsonHdlr(this->programName);
    QString instruction;
    QString operand1;
    QStringList args_str = this->statement.split(QRegExp("\\s*\"\\s*"), QString::SkipEmptyParts);

    if (args_str.size() == 2) // print a string
    {
        instruction = args_str[0];
        op1 = new Operand(new Variable(this->programName, args_str[1], ARRAY)); // say string is an array for now
    }
    else
    {
        QStringList args = this->statement.split(QRegExp("\\s+"), QString::SkipEmptyParts);

        if (args.size() != 2){
            if(args.size() == 1){
                return NO_OPERAND_ONE_ERROR;
            }
            else {
                return OPERAND_NUMBER_EXCEED_ERROR;
            }
        }

        instruction = args[0];
        this->op1 = new Operand(jsonHdlr.findVariable(args[1]));

        // Variable 1 not found
        if(this->op1->getIdentifier() == nullptr){
            return VARIABLE_ONE_NOT_FOUND_ERROR;
        }
    }

    QJsonObject op1Obj = JsonHandler::getJsonObj(OP_1, op1->getIdentifier()->getName());
    QJsonObject stmtObj = JsonHandler::getJsonObj(instruction, op1Obj);
    jsonHdlr.addElement(STMT, QString::number(lineNum), stmtObj);

    if (label)
    {
        jsonHdlr.addElement(LABEL, label->getName(), label->toJSON());
    }

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

    Variable* aVariable = static_cast<Variable*>(op1->getIdentifier());
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
