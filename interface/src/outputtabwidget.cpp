#include "../inc/outputtabwidget.h"
#include "./ui_outputtabwidget.h"

OutputTabWidget::OutputTabWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OutputTabWidget)
{
    ui->setupUi(this);
}

void OutputTabWidget::tabSetName(QString tabName){
    this->tabName = tabName;
}

void OutputTabWidget::setText(QString text){
    ui->textEdit->setText(text);
}

void OutputTabWidget::addText(QString text){
    ui->textEdit->append(text);
}

void OutputTabWidget::clearText(){
    ui->textEdit->clear();
}

QString OutputTabWidget::getTabName(){
    return tabName;
}

OutputTabWidget::~OutputTabWidget()
{
    delete ui;
}
