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
    for (qint16 i=0; i<this->numStmt; i++)
    {
        delete(this->statements[i]);
        this->numStmt--;
    }
}

ResultState Program::save()
{
    qDebug() << "RUNHE: Program::save()";
    QFile file(this->pgmPath + this->pgmName + ".scp");
    qint16 lineNum = 0;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return FILE_OPEN_ERROR;

    // read the file line by line
    while (!file.atEnd()) {
        QString line = file.readLine();
        lineNum++;
        // ignore comments
        if (line.startsWith("#"))
            continue;
        ResultState res = addStmt(line);
        // TODO: error recovery
        if (res != NO_ERROR)
            qDebug() << res << "at line " << lineNum;
    }

    file.close();
    return NO_ERROR;
}

ResultState Program::compile()
{
    qDebug() << "RUNHE: Program::compile()";
    // TODO: calling compile()
    // TODO: error recovery
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
    QStringList args = stmt.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    Statement* newStmt;
    // TODO: check label
    switch (this->getStmtId(args[0])) {
    case ADD_STMT:
        newStmt = new AddStmt(this->pgmName, stmt, nullptr);
        break;
    case CMP_STMT:
        newStmt = new CompStmt(this->pgmName, stmt, nullptr);
        break;
    case DCA_STMT:
        newStmt = new DeclArrStmt(this->pgmName, stmt, nullptr);
        break;
    case DCI_STMT:
        newStmt = new DeclIntStmt(this->pgmName, stmt, nullptr);
        break;
    case END_STMT:
        newStmt = new EndStmt(this->pgmName, stmt, nullptr);
        break;
    case JEQ_STMT:
        newStmt = new JEqStmt(this->pgmName, stmt, nullptr);
        break;
    case JLS_STMT:
        newStmt = new JLessStmt(this->pgmName, stmt, nullptr);
        break;
    case JMR_STMT:
        newStmt = new JMoreStmt(this->pgmName, stmt, nullptr);
        break;
    case JMP_STMT:
        newStmt = new JumpStmt(this->pgmName, stmt, nullptr);
        break;
    case MOV_STMT:
        newStmt = new MovStmt(this->pgmName, stmt, nullptr);
        break;
    case PRT_STMT:
        newStmt = new PrintStmt(this->pgmName, stmt, nullptr);
        break;
    case RDI_STMT:
        newStmt = new ReadStmt(this->pgmName, stmt, nullptr);
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
    else if(stmt == "mov")
        return MOV_STMT;
    else if(stmt == "prt")
        return PRT_STMT;
    else if(stmt == "rdi")
        return RDI_STMT;
    else
        return INVALID_STMT;
}
