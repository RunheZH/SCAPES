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
    this->op1 = new Variable(args[1], INT);

    JsonHandler jsonHdlr(this->programName);
    jsonHdlr.addElement(VAR, op1->getName(), op1->toJSON());

    QJsonObject op1Obj = jsonHdlr.getJsonObj(OP_1, args[1]);
    QJsonObject stmtObj = jsonHdlr.getJsonObj(instruction, op1Obj);
    jsonHdlr.addElement(STMT, QString::number(lineNum), stmtObj);

    if (label)
    {
        jsonHdlr.addElement(LABEL, label->getName(), label->toJSON());
    }

    return NO_ERROR;
}

ResultState DeclIntStmt::run()
{
    qDebug() << "DeclIntStmt.run()";
    return NO_ERROR;
}

