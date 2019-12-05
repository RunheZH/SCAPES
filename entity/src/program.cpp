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
    QFile file(this->pgmPath);
    int lineNum = 0;
    this->hasEnd = false;
    this->hasError = false;
    this->statements.clear();
    this->jumpStmts.clear();
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
    this->statements.clear();
    this->jumpStmts.clear();
    this->ids.clear();

    JsonHandler jsonHdlr(this->pgmName);
    QJsonObject jsonObj = jsonHdlr.read();

    // load labels
    QJsonObject labelObj = jsonObj[LABEL].toObject();
    for (QJsonObject::iterator it = labelObj.begin(); it != labelObj.end(); it++)
    {
        int lineNum = it.value().toObject().begin().value().toString().toInt();
        Label* label = new Label(this->tempFileName, it.key(), lineNum);
        ids.insert(it.key(), std::shared_ptr<Label>(label));
        JsonHandler jsonHdlr(this->tempFileName);
        jsonHdlr.addElement(LABEL, label->getName(), label->toJSON());
    }
    qDebug() << ids.keys();

    // load statements
    QJsonObject statementObj = jsonObj[STMT].toObject();

    // sorting by line number
    QStringList keys = statementObj.keys();
    QVector<int> keysToInt;
    for (int i = 0; i < keys.size(); i++)
    {
        keysToInt.append(keys[i].toInt());
    }
    std::sort(keysToInt.begin(), keysToInt.end());

    // compile
    for (QVector<int>::iterator it = keysToInt.begin(); it != keysToInt.end(); it++)
    {
        QJsonObject stmtObj = statementObj.find(QString::number(*it)).value().toObject();
        QString instruction = stmtObj.keys().begin()[0];
        QString op1 = stmtObj[instruction].toObject()[OP_1].toString();
        QString op2 = stmtObj[instruction].toObject()[OP_2].toString();

        // add current statement
        QString stmt = instruction + " " + op1 + " " + op2;
        ResultState re = addStmt(stmt, statementObj.find(QString::number(*it)).key().toInt());
        if (re != NO_ERROR)
        {
            errorControl->printErrorMsgAtLine(re, statementObj.find(QString::number(*it)).key().toInt());
        }
    }

    compile(true);

    return NO_ERROR;
}

ResultState Program::compile(bool isLoadFromJSON)
{
    ResultState res;
    if (!isLoadFromJSON)
    {
        res = this->save();
        if (res != NO_ERROR)
            return res;
    }

    this->jumpStmts.clear();
    QFile tmpFile(this->tempFileName + ".json");

    for(QMap<int, Statement*>::iterator it = this->statements.begin(); it != this->statements.end(); it++){
        if (isJumpStmt(it.value()))
        {
            this->jumpStmts.insert(it.key(), it.value());
            continue;
        }
        res = it.value()->compile();
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
    if (this->statements.isEmpty())
    {
        errorControl->printErrorMsg("Program has not been compiled yet.");
        return RUNTIME_ERROR;
    }
    ReturnValue* runResult;
    for (QMap<int, Statement*>::iterator it = this->statements.begin(); it != this->statements.end(); it++)
    {
        // has reached 'end'
        if (isEndStmt(it.value())) break;

        this->jumpToLineNum = it.key();
        runResult = it.value()->run();
        if (runResult->getResultState() != NO_ERROR)
        {
            this->errorControl->printErrorMsgAtLine(runResult->getResultState(), it.key());
            delete runResult;
            return RUNTIME_ERROR;
        }
        if (runResult->getJumpToLine() != NO_JUMP) // NO_ERROR
        {
            // jump to the given line
            if (dynamic_cast<JLessStmt*>(it.value()) && this->cmpResult == -1)
                this->jumpToLineNum = runResult->getJumpToLine();
            else if (dynamic_cast<JEqStmt*>(it.value()) && this->cmpResult == 0)
                this->jumpToLineNum = runResult->getJumpToLine();
            else if (dynamic_cast<JMoreStmt*>(it.value()) && this->cmpResult == 1)
                this->jumpToLineNum = runResult->getJumpToLine();
            else if (dynamic_cast<JumpStmt*>(it.value()))
                this->jumpToLineNum = runResult->getJumpToLine();
        }
        if (runResult->getCompareResult() != NO_CMP)
        {
            this->cmpResult = runResult->getCompareResult();
        }
        it = this->statements.find(this->jumpToLineNum);
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
        newStmt = new PrintStmt(this->tempFileName, stmt, this->ids, lineNum, errorControl);
        break;
    case RDI_STMT:
        newStmt = new ReadStmt(this->tempFileName, stmt, this->ids, lineNum, errorControl);
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
