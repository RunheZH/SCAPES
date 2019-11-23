#include "../inc/endStmt.h"

EndStmt::EndStmt(QString pgmName, QString stmt, Label* lbl, qint16 lnNum) : Statement(pgmName, stmt, lbl, lnNum)
{
    qDebug() << "EndStmt()";
}

EndStmt::~EndStmt()
{
    qDebug() << "~EndStmt()";
}

ResultState EndStmt::compile()
{
    qDebug() << "EndStmt.compile()";

    QStringList args = this->statement.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if (args.size() != 1){
        return OPERAND_NUMBER_EXCEED_ERROR;
    }

    QString instruction = args[0];
    JsonHandler jsonHdlr(this->programName);
    QJsonObject stmtObj = JsonHandler::getJsonObj(instruction, END);
    jsonHdlr.addElement(STMT, QString::number(lineNum), stmtObj);

    if (label)
    {
        jsonHdlr.addElement(LABEL, label->getName(), label->toJSON());
    }

    return NO_ERROR;
}

ResultState EndStmt::run()
{
    qDebug() << "EndStmt.run()";

    // return end;

    return NO_ERROR;
}
