#include "../inc/jumpStmt.h"

JumpStmt::JumpStmt(QString pgmName, QString stmt, QMap<QString, std::shared_ptr<Identifier>>& idsLib, int lnNum) : Statement(pgmName, stmt, idsLib, lnNum)
{
    qDebug() << "JumpStmt()";
}

JumpStmt::~JumpStmt()
{
    delete (op1.getIdentifier());
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

    return NO_ERROR;
}

ReturnValue* JumpStmt::run()
{
    qDebug() << "JumpStmt.run()";

    Label* aLabel = static_cast<Label*>(op1.getIdentifier());
    int lineNum = aLabel->getLineNum();

    return new ReturnValue(NO_ERROR, lineNum, NO_CMP);
}
