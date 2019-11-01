#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dirView();
    tabView();
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

//INITIALIZE TAB WIDGET
void MainWindow::tabView(){
    tabAdd();
//    fileText * ft = (fileText*) ui->tabWidget->widget(0);
//    ft->addtext();
}

//ADD NEW TAB ON TABWIDGET
void MainWindow::tabAdd(){
    ui->tabWidget->addTab(new tabchildwidget(), QString("newfile %0").arg(ui->tabWidget->count()+1));
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
}

//CHECK IF OPEN TAB IS ALREADY SHOWN
int MainWindow::tabIsExist(QString fileDir){
    for(int i=0; i<ui->tabWidget->count(); i++){
        tabchildwidget * ft = static_cast<tabchildwidget*>(ui->tabWidget->widget(i));
//        qDebug()<<fileDir+"  already: "+ft->getFileDir();
        if(fileDir==ft->getFileDir()){
            return i;       //if found tab exists file, return the tab index
        }
    }
    return -1;//not found return -1
}


//OPEN FILE FUNCTION-from tool bar
void MainWindow::openFile(){
    QString fileDir = QFileDialog::getOpenFileName(this,
            tr("Open the file"), "/home/student/Desktop",
            tr("SCAPES file (*.scp);;All Files (*)"));
    QFile file(fileDir);
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    currentFile = fileDir;
    QTextStream in(&file);
    QString text = in.readAll();
    tabchildwidget * ft = static_cast<tabchildwidget*>(ui->tabWidget->currentWidget());
    qDebug()<<"open file dir - " <<fileDir;
    //open the file already shown in the tab
    int tabIndex = tabIsExist(fileDir);
//    qDebug()<<"file tab index at - " <<tabIndex;
    if(tabIndex!=-1){
        ui->tabWidget->setCurrentIndex(tabIndex);
        ui->dirView->setCurrentIndex(dirmodel->index(fileDir));
        return;
    }
    //else file not show in the tab

    if((ui->tabWidget->count())==0){    //check if there are no tab
        tabAdd();
        ft = static_cast<tabchildwidget*>(ui->tabWidget->currentWidget());
    }else if(!ft->isEmpty()){           //check if there is at least one tab and if it is empty
        tabAdd();
        ft = static_cast<tabchildwidget*>(ui->tabWidget->currentWidget());
    }
    ft->setText(text);
    ft->storeFileDir(fileDir);
//    setWindowTitle(ft->getFileName());
    file.close();
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), ft->getFileName());
    ui->dirView->setCurrentIndex(dirmodel->index(fileDir));    //update file explorer
//    QMessageBox::information(this, "Open Complete", "Open file: " + file.fileName());
}

//OPEN FILE FUNCTION-from file directory
void MainWindow::openFile(const QModelIndex &index){
    QFile file(dirmodel->filePath(index));
    if(file.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream in(&file);
        QString text = in.readAll();
        tabchildwidget * ft = static_cast<tabchildwidget*>(ui->tabWidget->currentWidget());
        int tabIndex = tabIsExist(dirmodel->filePath(index));
        if(tabIndex!=-1){
            ui->tabWidget->setCurrentIndex(tabIndex);
            ui->dirView->setCurrentIndex(index);
            return;
        }

        if((ui->tabWidget->count())==0){    //check if there are no tab
            tabAdd();
            ft = static_cast<tabchildwidget*>(ui->tabWidget->currentWidget());
        }else if(!ft->isEmpty()){           //check if there is at least one tab and if it is empty
            tabAdd();
            ft = static_cast<tabchildwidget*>(ui->tabWidget->currentWidget());
        }
        ft->setText(text);
        ft->storeFileDir(dirmodel->filePath(index));
        ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), ft->getFileName());
        file.close();
    }
}

//SAVE FILE FUNCTION
void MainWindow::saveFile(){
    QString fileDir = QFileDialog::getSaveFileName(this,
            tr("Save SCAPES file"), "/home/student/Desktop/new file.scp",
            tr("SCAPES file (*.scp);;All Files (*)"));
    QFile file(fileDir);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileDir;
    QTextStream out(&file);
    tabchildwidget * ft = static_cast<tabchildwidget*>(ui->tabWidget->currentWidget());
    QString text = ft->getText();
    ft->storeFileDir(fileDir);
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), ft->getFileName());
    out<<text;
    file.close();
    ui->dirView->setCurrentIndex(dirmodel->index(fileDir));    //update file explorer
    QMessageBox::information(this, "Save Complete", "Save file: " + file.fileName());
}

//COMPILE TEXT FUNCTION
void MainWindow::compileText(QString fileText){
    qDebug()<<fileText;
    //RUNHE.compileProgram(fileText);
}

//showErrorMessage
void MainWindow::showErrorMessage(QString errorText){
    QMessageBox::warning(this, "Error", errorText);
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
    openFile();
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
    tabAdd();
}

void MainWindow::on_actionCompile_triggered()
{
    tabchildwidget * ft = static_cast<tabchildwidget*>(ui->tabWidget->currentWidget());
    QString fileText = ft->getText();
    compileText(fileText);
}

void MainWindow::on_actionRun_triggered()
{
    qDebug()<<ui->tabWidget->count();
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    tabchildwidget * ft = static_cast<tabchildwidget*>(ui->tabWidget->currentWidget());
    ui->tabWidget->removeTab(index);

}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    tabchildwidget * ft = static_cast<tabchildwidget*>(ui->tabWidget->widget(index));
    ui->dirView->setCurrentIndex(dirmodel->index(ft->getFileDir()));
}
