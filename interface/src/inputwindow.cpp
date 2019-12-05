#include "../inc/inputwindow.h"
#include "ui_inputwindow.h"

InputWindow::InputWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputWindow)
{
    ui->setupUi(this);
//    this->setWindowFlags ( Qt::CustomizeWindowHint | Qt::WindowTitleHint);
}

InputWindow::~InputWindow()
{
    delete ui;
}

int InputWindow::readValue(QString variableName){
    this->show();
    ui->label->setText("Please Input value for " + variableName);
    ui->lineEdit->setValidator(new QIntValidator(-100000, 100000, this)); //for now accept -100000 to 100000 integer input
    //wait until press okay
    QEventLoop loop;
    connect(this, SIGNAL(okayClicked()), &loop, SLOT(quit()));
    connect(this, SIGNAL(cancelClicked()), &loop, SLOT(quit()));
    connect(this, SIGNAL(windowClose()), &loop, SLOT(quit()));
    loop.exec();
    int value = -1000000;   //default value is out of input range, check if the value has input
    if(whichClicked == 1){
        QString input = ui->lineEdit->text();
        value = input.toInt();
    }
    return value;
}

void InputWindow::closeEvent(QCloseEvent *event){
   emit windowClose();
}


void InputWindow::on_okayButton_clicked()
{
    whichClicked = 1;
    emit okayClicked();
}

void InputWindow::on_cancelButton_clicked()
{
    whichClicked = 0;
    emit cancelClicked();
}
