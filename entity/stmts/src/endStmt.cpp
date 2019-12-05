#include "../inc/endStmt.h"

EndStmt::EndStmt(QString pgmName, QString stmt, QMap<QString, std::shared_ptr<Identifier>>& idsLib, int lnNum) : Statement(pgmName, stmt, idsLib, lnNum){}

EndStmt::~EndStmt(){}

ResultState EndStmt::compile()
{
    qDebug() << "EndStmt.compile()";
    QStringList args = this->statement.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if (args.size() != 1){ // syntax checking
        return OPERAND_NUMBER_EXCEED_ERROR;
    }

    // add to JSON file
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

    return new ReturnValue(NO_ERROR);
}
