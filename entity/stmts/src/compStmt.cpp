#include "../inc/compStmt.h"

CompStmt::CompStmt(QString pgmName, QString stmt, Label* lbl) : Statement(pgmName, stmt, lbl)
{
    qDebug() << "CompStmt()";
}

CompStmt::~CompStmt()
{
    qDebug() << "~CompStmt()";
}

ResultState CompStmt::compile()
{
    qDebug() << "CompStmt.compile()";
    QStringList args = this->statement.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if (args.size() != 3){
        if(args.size() == 1){
            return NO_OPERAND_ONE_ERROR;
        }
        if(args.size() == 2){
            return NO_OPERAND_TWO_ERROR;
        }
        else {
            return OPERAND_NUMBER_EXCEED_ERROR;
        }
    }

    QString instruction = args[0];
    QString operand1 = args[1];
    QString operand2 = args[2];
    ResultState res = NO_ERROR;

    JsonHandler* jsonHdl = new JsonHandler(this->programName);
    // TODO: not necessary to be ints
    QJsonObject firstQJsonObject = jsonHdl->findVariable(operand1);
    QJsonObject secondQJsonObject = jsonHdl->findVariable(operand2);

    /*
    // Variable 1 found
    if (firstQJsonObject != jsonHdl->getJsonFromStr("{}")){
        // Variable 2 found
        if (secondQJsonObject != jsonHdl->getJsonFromStr("{}")){
            QFile file(this->programName + ".json");
            if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
                // We're going to streaming text to the file
                QTextStream stream(&file);

                stream << "Center Point: " << iter_result[0] << "  " << iter_result[1]
                          << "  " << iter_result[2] << " Rotation: " << iter_result[3] <<'\n';

                file.close();
                qDebug() << "sucessfully wrote to file" << this->programName;
                res = NO_ERROR;
            }
            else{
                qDebug() << "File_open_error";
                res = FILE_OPEN_ERROR;
            }

        }
        // Variable 2 NOT found
        else {
            res = VARIABLE_TWO_NOT_FOUND_ERROR;
        }
    }
    // Variable 1 NOT found
    else{
        // Variable 2 found
        if (secondQJsonObject != jsonHdl->getJsonFromStr("{}")){
            res = VARIABLE_ONE_NOT_FOUND_ERROR;
        }
        // Variable 2 NOT found
        else {
            res = VARIABLE_ONE_AND_TWO_NOT_FOUND_ERROR;
        }
    }

    */
    delete(jsonHdl);
    return res;
}

ResultState CompStmt::run()
{
    qDebug() << "CompStmt.run()";
    return NO_ERROR;
}
