#include "../inc/mainwindow.h"
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
    QString sPath = "/";
    dirmodel = new QFileSystemModel(this);
    dirmodel->setRootPath(sPath);
    ui->dirView->setModel(dirmodel);
    ui->dirView->setRootIndex(dirmodel->setRootPath("/"));
    ui->dirView->hideColumn(1);
    ui->dirView->hideColumn(2);
    ui->dirView->hideColumn(3);
}

void MainWindow::dirUpdate(QString filePath){
    if(filePath!=""){
        ui->dirView->setCurrentIndex(dirmodel->index(filePath));
        return;
    }
    if(ui->tabWidget->count()>0){   //there is at least one tab opened, and switch to that tab file path in file explorer
        tabchildwidget * ft = static_cast<tabchildwidget*>(ui->tabWidget->currentWidget());
//                    qDebug()<<"getfilepath "<<ft->getFilePath();
        if(ft->getFilePath()==""){  //new file situation
            ui->dirView->selectionModel()->clearSelection();
            return;
        }
        ui->dirView->setCurrentIndex(dirmodel->index(ft->getFilePath()));
    }else{
        ui->dirView->selectionModel()->clearSelection();    //there is no tab opened, clear file explorer selection
    }

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
int MainWindow::tabIsExist(QString filePath){
    for(int i=0; i<ui->tabWidget->count(); i++){
        tabchildwidget * ft = static_cast<tabchildwidget*>(ui->tabWidget->widget(i));
//        qDebug()<<filePath+"  already: "+ft->getFilePath();
        if(filePath==ft->getFilePath()){
            return i;       //if found tab exists file, return the tab index
        }
    }
    return -1;//not found return -1
}


//OPEN FILE FUNCTION-from tool bar
void MainWindow::openFile(){
    QString filePath = QFileDialog::getOpenFileName(this,
            tr("Open the file"), QCoreApplication::applicationDirPath(),
            tr("SCAPES file (*.scp);;All Files (*)"));
    if(filePath == ""){ return; }
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    currentFile = filePath;
    QTextStream in(&file);
    QString text = in.readAll();
    tabchildwidget * ft = static_cast<tabchildwidget*>(ui->tabWidget->currentWidget());
    qDebug()<<"open file dir - " <<filePath;
    //open the file already shown in the tab
    int tabIndex = tabIsExist(filePath);
//    qDebug()<<"file tab index at - " <<tabIndex;
    if(tabIndex!=-1){
        ui->tabWidget->setCurrentIndex(tabIndex);
        dirUpdate(filePath);
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
    ft->setChanged(false);
    ft->storeFilePath(filePath);
//    setWindowTitle(ft->getFileName());
    file.close();
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), ft->getFileName());
    dirUpdate(filePath);
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
        ft->setChanged(false);
        ft->storeFilePath(dirmodel->filePath(index));
        ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), ft->getFileName());
        file.close();
    }
}

//SAVE FILE FUNCTION
int MainWindow::saveAsFile(){
    QString filePath = QFileDialog::getSaveFileName(this,
            tr("Save SCAPES file"), "/home/student/Desktop/new file.scp",
            tr("SCAPES file (*.scp);;All Files (*)"));
    QFile file(filePath);
    if(filePath == ""){ return -1; }
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return -2;
    }
    currentFile = filePath;
    QTextStream out(&file);
    tabchildwidget * ft = static_cast<tabchildwidget*>(ui->tabWidget->currentWidget());
    QString text = ft->getText();
    ft->storeFilePath(filePath);
    ft->setChanged(false);
    out<<text;
    file.close();
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), ft->getFileName());
    dirUpdate(filePath);

    //save control part
    SaveControl* savecontrol = new SaveControl(ft->getFileName(),ft->getFilePath());
    Program* pgm = savecontrol->save();
//    qDebug()<<"fileDir save as: "<<fileDir;
    if(programList.size()==0){
        programList.push_back({filePath,pgm});
        qDebug()<<"programList add new: {"<<filePath<<","<<pgm<<"}";
    }else {
        for(int i=0; i<programList.size(); i++){
            if(programList[i].first==filePath){
                programList[i].second = pgm;
                qDebug()<<"programList replace existed: {"<<filePath<<","<<pgm<<"}";
                break;
            }else if (i==programList.size()-1) {
                programList.push_back({filePath,pgm});
                qDebug()<<"programList add new: {"<<filePath<<","<<pgm<<"}";
                break;
            }
        }
    }
    delete(savecontrol);
    //QMessageBox::information(this, "Save Complete", "Save file: " + file.fileName());
    return 0;
}

void MainWindow::saveFile(){
    tabchildwidget * ft = static_cast<tabchildwidget*>(ui->tabWidget->currentWidget());
    QString filePath = ft->getFilePath();
//    qDebug()<<"fileDir: "<<fileDir;
    if(filePath==""){    //  it is new file
        saveAsFile();
    }else { //already existed file
        QFile file(filePath);
        if(!file.open(QFile::WriteOnly | QFile::Text)){
            QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
            return;
        }
        currentFile = filePath;
        QTextStream out(&file);
        tabchildwidget * ft = static_cast<tabchildwidget*>(ui->tabWidget->currentWidget());
        QString text = ft->getText();
        ft->storeFilePath(filePath);
        ft->setChanged(false);
        ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), ft->getFileName());
        out<<text;
        file.close();
        dirUpdate(filePath);

        //save control part
        SaveControl* sc = new SaveControl(ft->getFileName(),ft->getFilePath());
        Program* pgm = sc->save();
//        qDebug()<<"fileDir save as: "<<fileDir;
        if(programList.size()==0){
            programList.push_back({filePath,pgm});
            qDebug()<<"programList add new: {"<<filePath<<","<<pgm<<"}";
        }else {
            for(int i=0; i<programList.size(); i++){
                if(programList[i].first==filePath){
                    programList[i].second = pgm;
                    qDebug()<<"programList replace existed: {"<<filePath<<","<<pgm<<"}";
                    break;
                }else if (i==programList.size()-1) {
                    programList.push_back({filePath,pgm});
                    qDebug()<<"programList add new: {"<<filePath<<","<<pgm<<"}";
                    break;
                }
            }
        }
        QMessageBox::information(this, "Save Complete", "Save file: " + file.fileName());
    }
}

//COMPILE TEXT FUNCTION
void MainWindow::compileText(QString filePath){
    Program* pgm = nullptr;
    for(int i=0; i<programList.size();i++){
        if(programList[i].first==filePath){
            pgm = programList[i].second;
        }
    }
    if(pgm == nullptr){
        QMessageBox::warning(this,"ERROR","You must save before compile");
        return;
    }
    CompileControl* compileControl = new CompileControl(pgm);
    compileControl->compile();
    delete(compileControl);
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
    QMessageBox msgBox;
    msgBox.setText("The file has been modified.");
    msgBox.setInformativeText("Do you want to save your changes before compile?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Ignore | QMessageBox::Cancel);
    msgBox.setButtonText(QMessageBox::Save, "Save and compile");
    msgBox.setButtonText(QMessageBox::Ignore, "Compile the last save");
    msgBox.setDefaultButton(QMessageBox::Save);

    int ret = msgBox.exec();
    switch (ret) {
        case QMessageBox::Save:
            saveFile();
            break;
        case QMessageBox::Ignore:
            break;
        case QMessageBox::Cancel:
        // Cancel was clicked
            return;
        default:
        // should never be reached
            QMessageBox::warning(this, "Error", "Cannot save before compile");
            break;
    }

    tabchildwidget * ft = static_cast<tabchildwidget*>(ui->tabWidget->currentWidget());
    QString filePath = ft->getFilePath();
    compileText(filePath);
}

void MainWindow::on_actionRun_triggered()
{
    qDebug()<<ui->tabWidget->count();
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    tabchildwidget * ft = static_cast<tabchildwidget*>(ui->tabWidget->widget(index));
    QMessageBox msgBox;
    msgBox.setText("The file has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
//    qDebug()<<"ischanged "<<ft->isChanged();
    int ret;
    if(ft->isChanged()){
        ret = msgBox.exec();
//        qDebug()<<ret;
    }else {
        ret = 8388608;  //discard
    }
    switch (ret) {
        case QMessageBox::Save:
        // Save was clicked
            if(ft->getFilePath()!=""){
                //save to existed file
                saveFile();
                ui->tabWidget->removeTab(index);
                ft->~tabchildwidget();
//                if(ui->tabWidget->count()>0){   //only update file explorer when there is exist tab
//                    ft = static_cast<tabchildwidget*>(ui->tabWidget->currentWidget());
//    //                    qDebug()<<"getfiledir "<<ft->getFileDir();
//                    ui->dirView->setCurrentIndex(dirmodel->index(ft->getFilePath()));    //update file explorer
//                }else{
//                    ui->dirView->selectionModel()->clearSelection();
//                }
                dirUpdate("");
                break;
            }
            if(saveAsFile()!=-1){
                ui->tabWidget->removeTab(index);
                ft->~tabchildwidget();
                if(ui->tabWidget->count()>0){   //only update file explorer when there is exist tab
                    ft = static_cast<tabchildwidget*>(ui->tabWidget->currentWidget());
    //                    qDebug()<<"getfiledir "<<ft->getFileDir();
                    ui->dirView->setCurrentIndex(dirmodel->index(ft->getFilePath()));    //update file explorer
                }else{
                    ui->dirView->selectionModel()->clearSelection();
                }
            }
            break;
        case QMessageBox::Discard:
        // Don't Save was clicked
            ui->tabWidget->removeTab(index);
            ft->~tabchildwidget();
//            if(ui->tabWidget->count()>0){   //only update file explorer when there is exist tab
//                ft = static_cast<tabchildwidget*>(ui->tabWidget->currentWidget());
//                    qDebug()<<"getfiledir "<<ft->getFileDir();
//                ui->dirView->setCurrentIndex(dirmodel->index(ft->getFilePath()));    //update file explorer
//            }else{
//                ui->dirView->selectionModel()->clearSelection();
//            }
            dirUpdate("");
            break;
        case QMessageBox::Cancel:
        // Cancel was clicked
            break;
        default:
        // should never be reached
            QMessageBox::warning(this, "Error", "Cannot Close Tab");
            break;
    }
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    tabchildwidget * ft = static_cast<tabchildwidget*>(ui->tabWidget->widget(index));
    dirUpdate(ft->getFilePath());
}

void MainWindow::on_actionSave_As_triggered()
{
    saveAsFile();
}

//QUIT PROGRAM TRIGGER
void MainWindow::on_actionQuit_triggered()
{
//    for(int i=0; i<programList.size();i++){
//        Program* pgm = programList[i].second;
//        delete pgm;
//    }
    qApp->exit();
}
