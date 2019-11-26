#include "../inc/declIntStmt.h"

DeclIntStmt::DeclIntStmt(QString pgmName, QString stmt, Label* lbl, qint16 lnNum) : Statement(pgmName, stmt, lbl, lnNum)
{
    qDebug() << "DeclIntStmt()";
}

DeclIntStmt::~DeclIntStmt()
{
    delete (op1);
    qDebug() << "~DeclIntStmt()";
}

ResultState DeclIntStmt::compile()
{
    qDebug() << "DeclIntStmt.compile()";

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
    this->op1 = new Operand(new Variable(this->programName, args[1], INT));

    JsonHandler jsonHdlr(this->programName);
    jsonHdlr.addElement(VAR, op1->getIdentifier()->getName(), op1->getIdentifier()->toJSON());

    QJsonObject op1Obj = JsonHandler::getJsonObj(OP_1, args[1]);
    QJsonObject stmtObj = JsonHandler::getJsonObj(instruction, op1Obj);
    jsonHdlr.addElement(STMT, QString::number(lineNum), stmtObj);

    if (label)
    {
        jsonHdlr.addElement(LABEL, label->getName(), label->toJSON());
    }

    return NO_ERROR;
}

ReturnValue* DeclIntStmt::run()
{
    qDebug() << "DeclIntStmt.run()";

    op1->getIdentifier()->addToDB();

    return new ReturnValue(NO_ERROR, NO_JUMP, NO_CMP);
}

