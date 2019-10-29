#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dirView();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//DIRECTORY VIEW
void MainWindow::dirView(){
    QString sPath = "/home";
    dirmodel = new QFileSystemModel(this);
    dirmodel->setRootPath(sPath);
    ui->dirView->setModel(dirmodel);
    ui->dirView->setRootIndex(dirmodel->setRootPath("/home"));
    ui->dirView->hideColumn(1);
    ui->dirView->hideColumn(2);
    ui->dirView->hideColumn(3);
}

//OPEN FILE FUNCTION-from tool bar
void MainWindow::openFile(){
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open the file"), "/home/student/Desktop",
            tr("SCAPES file (*.scp);;All Files (*)"));
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
//    setWindowTitle(fileName);
    currentFile = fileName;
    QTextStream in(&file);
    QString text = in.readAll();
    ui->fileText->setText(text);
    file.close();
    ui->dirView->setCurrentIndex(dirmodel->index(fileName));    //update file explorer
//    QMessageBox::information(this, "Open Complete", "Open file: " + file.fileName());
}

//OPEN FILE FUNCTION-from file directory
void MainWindow::openFile(const QModelIndex &index){
    QFile file(dirmodel->filePath(index));
    if(file.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream in(&file);
        QString text = in.readAll();
        ui->fileText->setText(text);
        file.close();
    }
}

//SAVE FILE FUNCTION
void MainWindow::saveFile(){
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save SCAPES file"), "/home/student/Desktop/new file.scp",
            tr("SCAPES file (*.scp);;All Files (*)"));
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    QTextStream out(&file);
    QString text = ui->fileText->toPlainText();
    out<<text;
    file.close();
    ui->dirView->setCurrentIndex(dirmodel->index(fileName));    //update file explorer
    QMessageBox::information(this, "Save Complete", "Save file: " + file.fileName());
}


//ACTION BUTTON TRIGGER
//ABOUT TRIGGER
void MainWindow::on_actionAbout_SCAPES_triggered()
{
    QMessageBox::about(this, "About SCAPES", "SCAPES Version 0.1\n\n Developed by Team DOWHILE");
}

//SAVE FILE TRIGGER
void MainWindow::on_actionSave_triggered()
{
    saveFile();
}

//OPEN FILE TRIGGER
void MainWindow::on_actionOpen_triggered()
{
    if(!ui->fileText->document()->isEmpty()){
        QMessageBox msgBox;
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        switch (ret) {
         case QMessageBox::Save:
            // Save was clicked
            saveFile();
            openFile();
            break;
        case QMessageBox::Discard:
            // Don't Save was clicked
            openFile();
            break;
         case QMessageBox::Cancel:
            // Cancel was clicked
            break;
        default:
            // should never be reached
            openFile();
            break;
        }
    } else {
        openFile();
    }
}

//QUIT PROGRAM TRIGGER
void MainWindow::on_actionQuit_triggered()
{
    qApp->exit();
}

void MainWindow::on_dirView_doubleClicked(const QModelIndex &index)
{
    openFile(index);
}

void MainWindow::on_actionNew_triggered()
{
    if(!ui->fileText->document()->isEmpty()){
        QMessageBox msgBox;
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        switch (ret) {
         case QMessageBox::Save:
            // Save was clicked
            saveFile();
            ui->fileText->clear();
            break;
        case QMessageBox::Discard:
            // Don't Save was clicked
            ui->fileText->clear();
            break;
         case QMessageBox::Cancel:
            // Cancel was clicked
            break;
        default:
            // should never be reached
            ui->fileText->clear();
            break;
        }
    } else {
        ui->fileText->clear();
    }
}

void MainWindow::on_actionCompile_triggered()
{
    QString fileText = ui->fileText->toPlainText();
    compileText(fileText);
}

void MainWindow::compileText(QString fileText){
//    QDebug(fileText);
}
