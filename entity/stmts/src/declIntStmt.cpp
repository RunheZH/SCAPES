#include "../inc/declIntStmt.h"

#include<QApplication>
#include<QDebug>

DeclIntStmt::DeclIntStmt(QString pgmName, QString stmt, Label* lbl) : Statement(pgmName, stmt, lbl)
{
    qDebug() << "DeclIntStmt()";
}

DeclIntStmt::~DeclIntStmt()
{
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
    QString operand1 = args[1];

    JsonHandler* aJson = new JsonHandler(this->programName);
    QJsonObject aQJsonObject = aJson->getJsonFromStr("{\"name\":\"operand1\", \"type\":0}");
    aJson->addElement("variable", aQJsonObject);

    delete(aJson);

    return NO_ERROR;
}

ResultState DeclIntStmt::run()
{
    qDebug() << "DeclIntStmt.run()";
    return NO_ERROR;
}

