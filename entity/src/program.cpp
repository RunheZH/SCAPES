#include "../inc/program.h"

/*********************************** API ***************************************/

Program::Program(QString pgmName, QString pgmPath)
{
    this->pgmName = pgmName;
    this->pgmPath = pgmPath;
    this->numStmt = 0;
}

Program::~Program()
{
    for (qint16 i = 0; i < this->numStmt; i++)
    {
        delete(this->statements[i]);
        this->numStmt--;
    }
}

ResultState Program::save()
{
    qDebug() << "RUNHE: Program::save()";
    QFile file(this->pgmPath);
    qint16 lineNum = 0;
    this->numStmt = 0;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "File_open_error";
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
        ResultState res = addStmt(line);
        // TODO: error recovery
        if (res != NO_ERROR)
            qDebug() << res << " at line " << lineNum;
    }

    file.close();
    return NO_ERROR;
}

ResultState Program::compile()
{
    qDebug() << "RUNHE: Program::compile()";

    ResultState res;
    for(qint16 i = 0; i < this->numStmt; i++){
        res = this->statements[i]->compile();
        // TODO: error recovery
        if (res != NO_ERROR)
            qDebug() << res << " statement " << i;
    }
    return NO_ERROR;
}

ResultState Program::run()
{
    qDebug() << "RUNHE: Program::run()";
    // TODO
    return NO_ERROR;
}

/*********************************** private helper functions ***************************************/

ResultState Program::addStmt(QString stmt)
{
    qDebug() << stmt;
    QStringList args = stmt.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    Statement* newStmt = nullptr;
    Label* newLabel = nullptr;
    // empty line
    if (args.isEmpty()) return INVALID_STATEMENT;

    QString instruction = args[0];

    // TODO: check label
    if (args[0].startsWith("L")){
        qDebug() << "RUNHE: detected label";
        newLabel = new Label(args[0]);
        // TODO: get rid of the leading spaces
        stmt = stmt.mid(args[0].length() + 1);
        instruction = args[1];
    }

    switch (this->getStmtId(instruction)) {
    case ADD_STMT:
        newStmt = new AddStmt(this->pgmName, stmt, newLabel);
        break;
    case CMP_STMT:
        newStmt = new CompStmt(this->pgmName, stmt, newLabel);
        break;
    case DCA_STMT:
        newStmt = new DeclArrStmt(this->pgmName, stmt, newLabel);
        break;
    case DCI_STMT:
        newStmt = new DeclIntStmt(this->pgmName, stmt, newLabel);
        break;
    case END_STMT:
        newStmt = new EndStmt(this->pgmName, stmt, newLabel);
        break;
    case JEQ_STMT:
        newStmt = new JEqStmt(this->pgmName, stmt, newLabel);
        break;
    case JLS_STMT:
        newStmt = new JLessStmt(this->pgmName, stmt, newLabel);
        break;
    case JMR_STMT:
        newStmt = new JMoreStmt(this->pgmName, stmt, newLabel);
        break;
    case JMP_STMT:
        newStmt = new JumpStmt(this->pgmName, stmt, newLabel);
        break;
    case MOV_STMT:
        newStmt = new MovStmt(this->pgmName, stmt, newLabel);
        break;
    case PRT_STMT:
        newStmt = new PrintStmt(this->pgmName, stmt, newLabel);
        break;
    case RDI_STMT:
        newStmt = new ReadStmt(this->pgmName, stmt, newLabel);
        break;
    case INVALID_STMT:
        return INVALID_STATEMENT;
    }

    this->statements[this->numStmt] = newStmt;
    this->numStmt++;
    qDebug() << "added " << stmt;
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
    else if(stmt == "mov")
        return MOV_STMT;
    else if(stmt == "prt")
        return PRT_STMT;
    else if(stmt == "rdi")
        return RDI_STMT;
    else
        return INVALID_STMT;
}
