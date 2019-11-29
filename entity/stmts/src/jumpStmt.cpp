#include "../inc/jumpStmt.h"

JumpStmt::JumpStmt(QString pgmName, QString stmt, Label* lbl, qint16 lnNum) : Statement(pgmName, stmt, lbl, lnNum)
{
    qDebug() << "JumpStmt()";
}

JumpStmt::~JumpStmt()
{
    delete (&op1);
    qDebug() << "~JumpStmt()";
}

ResultState JumpStmt::compile()
{
    qDebug() << "JumpStmt.compile()";

    QStringList args = this->statement.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if (args.size() != 2){
        if(args.size() == 1){
            return NO_OPERAND_ONE_ERROR;
        }
        else {
            return OPERAND_NUMBER_EXCEED_ERROR;
        }
    }

    JsonHandler jsonHdlr(this->programName);
    QString instruction = args[0];
    QString operand1 = args[1];

    op1.setIdentifier(jsonHdlr.findLabel(operand1));

    // Label 1 not found
    if(this->op1.getIdentifier() == nullptr){
        return LABEL_NOT_FOUND_ERROR;
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

ReturnValue* JumpStmt::run()
{
    qDebug() << "JumpStmt.run()";
    return new ReturnValue(NO_ERROR, NO_JUMP, NO_CMP);
}
