#include "../inc/endStmt.h"

EndStmt::EndStmt(QString pgmName, QString stmt, QMap<QString, std::shared_ptr<Identifier>>& idsLib, int lnNum) : Statement(pgmName, stmt, idsLib, lnNum)
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

    return NO_ERROR;
}

ReturnValue* EndStmt::run()
{
    qDebug() << "EndStmt.run()";

    // return end;

    return new ReturnValue(NO_ERROR, NO_JUMP, NO_CMP);
}
