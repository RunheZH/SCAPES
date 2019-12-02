#include "../inc/program.h"

/*********************************** API ***************************************/

Program::Program(QString pgmPath, OutputTabWidget* consoleTab, OutputTabWidget* errorTab)
{
    QStringList fileName = pgmPath.split(QRegExp(".scp"), QString::SkipEmptyParts);
    this->pgmName = fileName[0];
    this->tempFileName = this->pgmName + "_tmp";
    this->pgmPath = pgmPath;
    this->cmpResult = NO_CMP;
    this->jumpToLineNum = NO_JUMP;
    this->hasEnd = false;
    this->hasError = false;
    this->errorControl = new ErrorControl(consoleTab, errorTab);
}

Program::~Program()
{
    this->statements.clear();
    this->jumpStmts.clear(); // TODO: double deletion?
    this->ids.clear();

    delete errorControl;
}

ResultState Program::save()
{
    qDebug() << "RUNHE: Program::save()";
    QFile file(this->pgmPath);
    int lineNum = 0;
    this->hasEnd = false;
    this->hasError = false;
    this->statements.clear();
    this->ids.clear();

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        this->errorControl->printErrorMsg(FILE_OPEN_ERROR);
        return FILE_OPEN_ERROR;
    }

    // read the file line by line
    while (!file.atEnd()) {
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

ResultState Program::loadFromJSON()
{
    QFile jsonFile(this->pgmName + ".json");
    JsonHandler jsonHdlr(this->pgmName);

    //QJsonObject jsonObj = jsonHdlr.read();

    //TODO: convert json to statements

    return NO_ERROR;
}

ResultState Program::compile()
{
    qDebug() << "RUNHE: Program::compile()";

    ResultState res;
    res = this->save();
    if (res != NO_ERROR)
        return res;

    QFile tmpFile(this->tempFileName + ".json");

    this->jumpStmts.clear();
    for(QMap<int, Statement*>::iterator it = this->statements.begin(); it != this->statements.end(); it++){
        if (isJumpStmt(it.value()))
        {
            this->jumpStmts.insert(it.key(), it.value());
            continue;
        }
        // TODO: if it's cmp, check for at least one of the conditional jump statements
        res = it.value()->compile();
        qDebug() << ids.keys();
        qDebug() << ids.size();
        // error recovery
        if (res != NO_ERROR)
        {
            this->hasError = true;
            int lineNum = it.key();
            this->errorControl->printErrorMsgAtLine(res, lineNum);
        }
        else // no syntax error
        {
            if (isEndStmt(it.value()))
            {
                this->hasEnd = true;
            }
        }
    }

    if (!this->hasEnd) // unsuccessful compilation, remove .json file
    {
        this->errorControl->printErrorMsg(NO_END);
        tmpFile.remove();
        return COMPILATION_ERROR;
    }

    for (QMap<int, Statement*>::iterator it = this->jumpStmts.begin(); it != this->jumpStmts.end(); it++){
        res = it.value()->compile();
        qDebug() << ids.size();
        // error recovery
        if (res != NO_ERROR)
        {
            this->hasError = true;
            int lineNum = it.key();
            this->errorControl->printErrorMsgAtLine(res, lineNum);
        }
    }

    if (!this->hasError)
    {
        QFile realFile(this->pgmName + ".json");
        realFile.remove();
        tmpFile.rename(this->pgmName + ".json");
        return NO_ERROR;
    }
    tmpFile.remove();
    return COMPILATION_ERROR;
}

ResultState Program::run()
{
    qDebug() << "RUNHE: Program::run()";
    // init DB
    DBManager db(this->tempFileName);
    db.createDB();

    // adding labels to DB
    for (QMap<QString, std::shared_ptr<Identifier>>::iterator it = ids.begin(); it != ids.end(); it++)
    {
        it.value()->addToDB();
    }

    ReturnValue* runResult;
    for (QMap<int, Statement*>::iterator it = this->statements.begin(); it != this->statements.end(); it++)
    {
        // has reached 'end'
        if (isEndStmt(it.value())) break;

        runResult = it.value()->run();
        if (runResult->getResultState() != NO_ERROR)
        {
            this->errorControl->printErrorMsgAtLine(runResult->getResultState(), it.key());
            return RUNTIME_ERROR;
        }
        if (runResult->getJumpToLine() != NO_JUMP) // NO_ERROR
        {
            // jump to the given line
            it = this->statements.find(runResult->getJumpToLine());
            continue;
        }
        if (runResult->getCompareResult() != NO_CMP)
        {
            this->cmpResult = runResult->getCompareResult();
            switch (runResult->getCompareResult()) {
            case -1:
                //this->jumpToJls();
                break;
            case 0:
                //this->jumpToJeq();
                break;
            case 1:
                //this->jumpToJmr();
                break;
            default:
                errorControl->printErrorMsg("CMP returned wrong value: " + QString::number(runResult->getCompareResult()));
            }
        }
        delete runResult; // avoid memory leak
    }
    return NO_ERROR;
}

/*********************************** private helper functions ***************************************/

ResultState Program::addStmt(QString stmt, int lineNum)
{
    QStringList args = stmt.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    Statement* newStmt = nullptr;
    // empty line
    if (args.isEmpty()) return NO_ERROR;

    QString instruction = args[0];

    if (args[0].endsWith(":")){ // detected label
        instruction = args[1];
    }

    switch (this->getStmtId(instruction)) {
    case ADD_STMT:
        newStmt = new AddStmt(this->tempFileName, stmt, this->ids, lineNum);
        break;
    case CMP_STMT:
        newStmt = new CompStmt(this->tempFileName, stmt, this->ids, lineNum);
        break;
    case DCA_STMT:
        newStmt = new DeclArrStmt(this->tempFileName, stmt, this->ids, lineNum);
        break;
    case DCI_STMT:
        newStmt = new DeclIntStmt(this->tempFileName, stmt, this->ids, lineNum);
        break;
    case END_STMT:
        newStmt = new EndStmt(this->tempFileName, stmt, this->ids, lineNum);
        break;
    case JEQ_STMT:
        newStmt = new JEqStmt(this->tempFileName, stmt, this->ids, lineNum);
        break;
    case JLS_STMT:
        newStmt = new JLessStmt(this->tempFileName, stmt, this->ids, lineNum);
        break;
    case JMR_STMT:
        newStmt = new JMoreStmt(this->tempFileName, stmt, this->ids, lineNum);
        break;
    case JMP_STMT:
        newStmt = new JumpStmt(this->tempFileName, stmt, this->ids, lineNum);
        break;
    case MOV_STMT:
        newStmt = new MovStmt(this->tempFileName, stmt, this->ids, lineNum);
        break;
    case PRT_STMT:
        newStmt = new PrintStmt(this->tempFileName, stmt, this->ids, lineNum);
        break;
    case RDI_STMT:
        newStmt = new ReadStmt(this->tempFileName, stmt, this->ids, lineNum);
        break;
    case INVALID_STMT:
        return INVALID_STATEMENT;
    }

    this->statements.insert(lineNum, newStmt);
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
