#include "../inc/printStmt.h"

PrintStmt::PrintStmt(QString pgmName, QString stmt, QMap<QString, std::shared_ptr<Identifier>>& idsLib,
                     int lnNum, ErrorControl* errorControl) : Statement(pgmName, stmt, idsLib, lnNum)
{
    this->errorControl = errorControl;
}

PrintStmt::~PrintStmt()
{
    delete (op1.getIdentifier());
}

ResultState PrintStmt::compile()
{
    JsonHandler jsonHdlr(this->programName);
    QString instruction;
    QString operand1;
    QRegExp str_pattern("\"*\"");
    if (statement.contains(str_pattern)) // print a string
    {
        QStringList args_str = this->statement.split(QRegExp("\\s*\"\\s*"), QString::SkipEmptyParts);

        if (args_str.size() != 2){ // syntax checking
            if(args_str.size() == 1){
                return NO_OPERAND_ONE_ERROR;
            }
            else {
                return OPERAND_NUMBER_EXCEED_ERROR;
            }
        }
        instruction = args_str[0];
        operand1 = "\"" + args_str[1] + "\"";
        // save the value to print out in Operand class only
        // b/c it is not a variable, nor an element of an array
        op1.setValue(args_str[1]);
        op1.setIsLiteral(true);
        op1.setIsStr(true);
    }
    else // print a literal, int, or an element of an array
    {
        QStringList args = this->statement.split(QRegExp("\\s+"), QString::SkipEmptyParts);

        if (args.size() != 2){ // syntax checking
            if(args.size() == 1){
                return NO_OPERAND_ONE_ERROR;
            }
            else {
                return OPERAND_NUMBER_EXCEED_ERROR;
            }
        }

        instruction = args[0];
        operand1 = args[1];

        ResultState re = checkVariable(operand1, op1, true); // checkLiteral set to true
        if (re != NO_ERROR)
            return re;
    }

    // add to JSON file
    QJsonObject op1Obj;
    op1Obj = JsonHandler::getJsonObj(OP_1, operand1);

    QJsonObject stmtObj = JsonHandler::getJsonObj(instruction, op1Obj);
    jsonHdlr.addElement(STMT, QString::number(lineNum), stmtObj);

    return NO_ERROR;
}

ReturnValue* PrintStmt::run()
{
    if (op1.getIsLiteral())
    {
        if (op1.getIsStr()) // string
            errorControl->printToConsole(op1.getPValue());
        else // number
            errorControl->printToConsole(QString::number(op1.getValue()));
    }
    else if (dynamic_cast<Variable*>(op1.getIdentifier())->getType() == ARRAY) // array element
        errorControl->printToConsole(QString::number(dynamic_cast<Variable*>(op1.getIdentifier())->getValue(op1.getIndex())));
    else // int
        errorControl->printToConsole(QString::number(dynamic_cast<Variable*>(op1.getIdentifier())->getValue(0)));

    return new ReturnValue(NO_ERROR);
}
