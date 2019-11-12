#include "../inc/readStmt.h"

ReadStmt::ReadStmt(QString pgmName, QString stmt, Label* lbl, qint16 lnNum) : Statement(pgmName, stmt, lbl, lnNum)
{
    qDebug() << "ReadStmt()";
}

ReadStmt::~ReadStmt()
{
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
    QJsonObject aQJsonObject = jsonHdlr.findVariable(operand1);

    // Variable 1 not found
    if(aQJsonObject == jsonHdlr.getJsonFromStr("{}")){
        return VARIABLE_ONE_NOT_FOUND_ERROR;
    }

    QJsonObject op1Obj = jsonHdlr.getJsonObj(OP_1, operand1);
    QJsonObject stmtObj = jsonHdlr.getJsonObj(instruction, op1Obj);
    jsonHdlr.addElement(STMT, QString::number(lineNum), stmtObj);

    if (label)
    {
        jsonHdlr.addElement(LABEL, label->getName(), label->toJSON());
    }

    return NO_ERROR;
}

ResultState ReadStmt::run()
{
    qDebug() << "ReadStmt.run()";
    return NO_ERROR;
}
