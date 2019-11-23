#include "../inc/inputwindow.h"
#include "ui_inputwindow.h"

InputWindow::InputWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputWindow)
{
    ui->setupUi(this);
}

InputWindow::~InputWindow()
{
    delete ui;
}

int InputWindow::readValue(QString variableName){
    QThread thread;
    thread.start();

    //connect(this, SLOT(on_okayButton_clicked()), thread, SLOT(quit));

        // Do other stuff.
        // ... stuff

        int returnValue = QApplication::exec();
        thread.wait();
    this->show();
    ui->label->setText("Please Input value for " + variableName);
    on_okayButton_clicked();
}



void InputWindow::on_okayButton_clicked()
{
    if(ui->textEdit->toPlainText()!=""){
        qDebug()<<"correct";
    }
}
