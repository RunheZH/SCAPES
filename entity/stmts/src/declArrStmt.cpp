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

    // check if a valid size is given
    bool vaildSize;
    QString instruction = args[0];
    QString varName = args[1];
    QString arrSize = args[2];
    int maxSize = arrSize.toInt(&vaildSize);
    if (!vaildSize || maxSize < 1) {
        return INVALID_OPERAND;
    }

    // declare an array
    Variable* newVar = new Variable(this->programName, varName, ARRAY, maxSize);
    op1.setIdentifier(newVar);
    ids.insert(varName, std::shared_ptr<Variable>(newVar));

    // add to JSON file
    JsonHandler jsonHdlr(this->programName);
    jsonHdlr.addElement(VAR, op1.getIdentifier()->getName(), op1.getIdentifier()->toJSON());

    QJsonObject op1Obj = JsonHandler::getJsonObj(OP_1, varName);
    QJsonObject op2Obj = JsonHandler::getJsonObj(OP_2, arrSize);
    QJsonObject stmtObj = JsonHandler::getJsonObj(instruction, JsonHandler::appendToEnd(op1Obj, op2Obj));
    jsonHdlr.addElement(STMT, QString::number(lineNum), stmtObj);

    return NO_ERROR;
}

ReturnValue* DeclArrStmt::run()
{
    qDebug() << "DeclArrStmt().run()";
    return new ReturnValue(NO_ERROR, NO_JUMP, NO_CMP);
}
