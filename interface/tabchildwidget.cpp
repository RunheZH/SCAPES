#include "tabchildwidget.h"
#include "ui_tabchildwidget.h"

tabchildwidget::tabchildwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tabchildwidget)
{
    ui->setupUi(this);
}

tabchildwidget::~tabchildwidget()
{
    delete ui;
}

void tabchildwidget::setText(QString text){
    ui->textEdit->setText(text);
}

QString tabchildwidget::getText(){
    return ui->textEdit->toPlainText();
}

bool tabchildwidget::isEmpty(){
    if(ui->textEdit->document()->isEmpty()){
        return true;
    }else{
        return false;
    }
}

void tabchildwidget::clearText(){
    ui->textEdit->clear();
}

void tabchildwidget::storeFileDir(QString fileDir){
    this->fileDir = fileDir;
}

QString tabchildwidget::getFileDir(){
    return fileDir;
}

QString tabchildwidget::getFileName(){
    QString fileName = fileDir.section("/",-1,-1);
    return fileName;
}
