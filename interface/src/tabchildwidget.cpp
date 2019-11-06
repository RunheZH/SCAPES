#include "../inc/tabchildwidget.h"
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
    qDebug()<<ui->textEdit->document();
    if(ui->textEdit->document()->isEmpty()){
        return true;
    }else{
        return false;
    }
}

void tabchildwidget::clearText(){
    ui->textEdit->clear();
}

void tabchildwidget::storeFilePath(QString filePath){
    this->filePath = filePath;
}

QString tabchildwidget::getFilePath(){
    return filePath;
}

QString tabchildwidget::getFileName(){
    QString fileName = filePath.section("/",-1,-1);
    return fileName;
}

void tabchildwidget::on_textEdit_textChanged()
{
    changed = true;
}

bool tabchildwidget::isChanged(){
    return changed;
}

void tabchildwidget::setChanged(bool changed){
    this->changed = changed;
}
