#include "../inc/declArrStmt.h"

DeclArrStmt::DeclArrStmt(QString pgmName, QString stmt, QMap<QString, std::shared_ptr<Identifier>>& idsLib, int lnNum) : Statement(pgmName, stmt, idsLib, lnNum)
{
    qDebug() << "DeclArrStmt()";
}

DeclArrStmt::~DeclArrStmt()
{
    delete (op1.getIdentifier());
    qDebug() << "~DeclArrStmt()";
}

ResultState DeclArrStmt::compile()
{
    qDebug() << "DeclArrStmt().compile()";

    QStringList args = this->statement.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if (args.size() != 3) {
        if (args.size() == 1) {
            return NO_OPERAND_ONE_ERROR;
        } else if (args.size() == 2) {
            return NO_OPERAND_TWO_ERROR;
        } else {
            return OPERAND_NUMBER_EXCEED_ERROR;
        }
    }

    bool vaildSize;
    QString instruction = args[0];
    int maxSize = args[2].toInt(&vaildSize);
    if (!vaildSize || maxSize < 1) {
        return INVALID_OPERAND;
    }
    op1.setIdentifier(new Variable(this->programName, args[1], ARRAY, maxSize));

    JsonHandler jsonHdlr(this->programName);
    jsonHdlr.addElement(VAR, op1.getIdentifier()->getName(), op1.getIdentifier()->toJSON());

    QJsonObject op1Obj = JsonHandler::getJsonObj(OP_1, args[1]);
    QJsonObject stmtObj = JsonHandler::getJsonObj(instruction, op1Obj);
    jsonHdlr.addElement(STMT, QString::number(lineNum), stmtObj);

    return NO_ERROR;
}

ReturnValue* DeclArrStmt::run()
{
    qDebug() << "DeclArrStmt().run()";
    return new ReturnValue(NO_ERROR, NO_JUMP, NO_CMP);
}
