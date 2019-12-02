#include "../inc/declIntStmt.h"

DeclIntStmt::DeclIntStmt(QString pgmName, QString stmt, QMap<QString, std::shared_ptr<Identifier>>& idsLib, int lnNum) : Statement(pgmName, stmt, idsLib, lnNum)
{
    qDebug() << "DeclIntStmt()";
}

DeclIntStmt::~DeclIntStmt()
{
    delete (op1.getIdentifier());
    qDebug() << "~DeclIntStmt()";
}

ResultState DeclIntStmt::compile()
{
    qDebug() << "DeclIntStmt.compile()";

    QStringList args = this->statement.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if (args.size() != 2){ // syntax checking
        if(args.size() == 1){
            return NO_OPERAND_ONE_ERROR;
        }
        else {
            return OPERAND_NUMBER_EXCEED_ERROR;
        }
    }

    QString instruction = args[0];
    Variable* newVar = new Variable(this->programName, args[1], INT);
    op1.setIdentifier(newVar);
    ids.insert(newVar->getName(), std::shared_ptr<Variable>(newVar));

    // add to JSON file
    JsonHandler jsonHdlr(this->programName);
    jsonHdlr.addElement(VAR, op1.getIdentifier()->getName(), op1.getIdentifier()->toJSON());

    QJsonObject op1Obj = JsonHandler::getJsonObj(OP_1, args[1]);
    QJsonObject stmtObj = JsonHandler::getJsonObj(instruction, op1Obj);
    jsonHdlr.addElement(STMT, QString::number(lineNum), stmtObj);

    return NO_ERROR;
}

ReturnValue* DeclIntStmt::run()
{
    qDebug() << "DeclIntStmt.run()";

    op1.getIdentifier()->addToDB();

    return new ReturnValue(NO_ERROR, NO_JUMP, NO_CMP);
}

