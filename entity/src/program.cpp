#include "../inc/program.h"

/*********************************** API ***************************************/

Program::Program(QString pgmPath, OutputTabWidget* consoleTab, OutputTabWidget* errorTab)
{
    QStringList fileName = pgmPath.split(QRegExp(".scp"), QString::SkipEmptyParts);
    this->pgmName = fileName[0];
    this->pgmPath = pgmPath;
    this->numStmt = 0;
    this->numLabel = 0;
    this->numJumpStmt = 0;
    this->hasEnd = false;
    this->hasError = false;
    this->errorControl = new ErrorControl(consoleTab, errorTab);
}

Program::~Program()
{
    for (qint16 i = 0; i < this->numStmt; i++)
    {
        delete (this->statements[i]);
    }

    for (qint16 i = 0; i < this->numLabel; i++)
    {
        delete (this->ids[i]);
    }

    for (qint16 i = 0; i < this->numJumpStmt; i++)
    {
        delete (this->jumpStmts[i]);
    }

    delete (errorControl);
}

ResultState Program::save()
{
    qDebug() << "RUNHE: Program::save()";
    QFile file(this->pgmPath);
    qint16 lineNum = 0;
    this->numStmt = 0;
    this->numLabel = 0;
    this->hasEnd = false;
    this->hasError = false;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        this->errorControl->printErrorMsg(FILE_OPEN_ERROR);
        return FILE_OPEN_ERROR;
    }

    // read the file line by line
    while (!file.atEnd()) {
        // TODO: need to get rid of '\n'
        QString line = file.readLine();
        lineNum++;
        // ignore comments
        if (line.startsWith("#"))
            continue;
        ResultState res = addStmt(line, lineNum);
        // error recovery
        if (res != NO_ERROR)
        {
            this->hasError = true;
            errorControl->printErrorMsgAtLine(res, lineNum);
        }
    }

    file.close();
    return NO_ERROR;
}

ResultState Program::compile()
{
    qDebug() << "RUNHE: Program::compile()";

    QFile file(this->pgmName + ".json");
    file.remove();

    ResultState res;
    this->numJumpStmt = 0;
    for(qint16 i = 0; i < this->numStmt; i++){
        if (isJumpStmt(this->statements[i]))
        {
            this->jumpStmts[this->numJumpStmt] = this->statements[i];
            this->numJumpStmt++;
            continue;
        }
        res = this->statements[i]->compile();
        // error recovery
        if (res != NO_ERROR)
        {
            this->hasError = true;
            qint16 lineNum = this->statements[i]->getLineNum();
            this->errorControl->printErrorMsgAtLine(res, lineNum);
        }
        else // no syntax error
        {
            if (isEndStmt(this->statements[i]))
            {
                this->hasEnd = true;
            }
        }
    }

    if (!this->hasEnd)
    {
        this->errorControl->printErrorMsg(NO_END);
        return COMPILATION_ERROR;
    }

    for (qint16 i = 0; i < this->numJumpStmt; i++){
        res = this->jumpStmts[i]->compile();
        // error recovery
        if (res != NO_ERROR)
        {
            this->hasError = true;
            qint16 lineNum = this->jumpStmts[i]->getLineNum();
            this->errorControl->printErrorMsgAtLine(res, lineNum);
        }
    }

    if (!this->hasError)
        return NO_ERROR;
    return COMPILATION_ERROR;
}

ResultState Program::run()
{
    qDebug() << "RUNHE: Program::run()";
    // TODO: D2
    return NO_ERROR;
}

/*********************************** private helper functions ***************************************/

ResultState Program::addStmt(QString stmt, qint16 lineNum)
{
    QStringList args = stmt.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    Statement* newStmt = nullptr;
    Label* newLabel = nullptr;
    // empty line
    if (args.isEmpty()) return NO_ERROR;

    QString instruction = args[0];

    if (args[0].endsWith(":")){
        //qDebug() << "RUNHE: detected label";
        newLabel = new Label(args[0].left(args[0].lastIndexOf(":")), lineNum);
        ids[this->numLabel] = newLabel;
        // get rid of the leading spaces
        stmt = stmt.mid(args[0].length() + 1);
        instruction = args[1];
    }

    switch (this->getStmtId(instruction)) {
    case ADD_STMT:
        newStmt = new AddStmt(this->pgmName, stmt, newLabel, lineNum);
        break;
    case CMP_STMT:
        newStmt = new CompStmt(this->pgmName, stmt, newLabel, lineNum);
        break;
    case DCA_STMT:
        newStmt = new DeclArrStmt(this->pgmName, stmt, newLabel, lineNum);
        break;
    case DCI_STMT:
        newStmt = new DeclIntStmt(this->pgmName, stmt, newLabel, lineNum);
        break;
    case END_STMT:
        newStmt = new EndStmt(this->pgmName, stmt, newLabel, lineNum);
        break;
    case JEQ_STMT:
        newStmt = new JEqStmt(this->pgmName, stmt, newLabel, lineNum);
        break;
    case JLS_STMT:
        newStmt = new JLessStmt(this->pgmName, stmt, newLabel, lineNum);
        break;
    case JMR_STMT:
        newStmt = new JMoreStmt(this->pgmName, stmt, newLabel, lineNum);
        break;
    case JMP_STMT:
        newStmt = new JumpStmt(this->pgmName, stmt, newLabel, lineNum);
        break;
    case MOV_STMT:
        newStmt = new MovStmt(this->pgmName, stmt, newLabel, lineNum);
        break;
    case PRT_STMT:
        newStmt = new PrintStmt(this->pgmName, stmt, newLabel, lineNum);
        break;
    case RDI_STMT:
        newStmt = new ReadStmt(this->pgmName, stmt, newLabel, lineNum);
        break;
    case INVALID_STMT:
        return INVALID_STATEMENT;
    }

    this->statements[this->numStmt] = newStmt;
    this->numStmt++;
    return NO_ERROR;
}

StatementId Program::getStmtId(QString stmt)
{
    if(stmt == "add")
        return ADD_STMT;
    else if(stmt == "cmp")
        return CMP_STMT;
    else if(stmt == "dca")
        return DCA_STMT;
    else if(stmt == "dci")
        return DCI_STMT;
    else if(stmt == "end")
        return END_STMT;
    else if(stmt == "jeq")
        return JEQ_STMT;
    else if(stmt == "jls")
        return JLS_STMT;
    else if(stmt == "jmr")
        return JMR_STMT;
    else if(stmt == "jmp")
        return JMP_STMT;
    else if(stmt == "mov")
        return MOV_STMT;
    else if(stmt == "prt")
        return PRT_STMT;
    else if(stmt == "rdi")
        return RDI_STMT;
    else
        return INVALID_STMT;
}

bool Program::isEndStmt(Statement* stmt)
{
    if (dynamic_cast<EndStmt*>(stmt))
        return true;
    return false;
}

bool Program::isJumpStmt(Statement* stmt)
{
    if (dynamic_cast<JumpStmt*>(stmt))
        return true;
    else if (dynamic_cast<JLessStmt*>(stmt))
        return true;
    else if (dynamic_cast<JMoreStmt*>(stmt))
        return true;
    else if (dynamic_cast<JEqStmt*>(stmt))
        return true;
    return false;
}
