#include "../inc/declIntStmt.h"

#include<QApplication>
#include<QDebug>

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

    JsonHandler* jsonHdlr = new JsonHandler(this->programName);
    jsonHdlr->addElement("variable", op1->getName(), op1->toJSON());

    QJsonObject op1Obj = jsonHdlr->getJsonObj("op1", args[1]);
    QJsonObject stmtObj = jsonHdlr->getJsonObj("dci", op1Obj);
    jsonHdlr->addElement("statement", QString::number(lineNum), stmtObj);

    if (label)
    {
        jsonHdlr->addElement("label", label->getName(), label->toJSON());
    }

    delete (jsonHdlr);
    return NO_ERROR;
}

ResultState DeclIntStmt::run()
{
    qDebug() << "DeclIntStmt.run()";
    return NO_ERROR;
}

