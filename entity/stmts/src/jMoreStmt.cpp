#include "../inc/jMoreStmt.h"

JMoreStmt::JMoreStmt(QString pgmName, QString stmt, Label* lbl, qint16 lnNum) : Statement(pgmName, stmt, lbl, lnNum)
{
    qDebug() << "JMoreStmt()";
}

JMoreStmt::~JMoreStmt()
{
    qDebug() << "~JMoreStmt()";
}

ResultState JMoreStmt::compile()
{
    qDebug() << "JMoreStmt.compile()";
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

    QJsonObject aQJsonObject = jsonHdlr.findLabel(operand1);

    // Label 1 not found
    if(aQJsonObject == jsonHdlr.getJsonFromStr("{}")){
        return LABEL_NOT_FOUND_ERROR;
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

ResultState JMoreStmt::run()
{
    qDebug() << "JMoreStmt.run()";
    return NO_ERROR;
}
