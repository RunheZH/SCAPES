#include "../inc/opennewwidget.h"
#include "ui_opennewwidget.h"

OpenNewWidget::OpenNewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OpenNewWidget)
{
    ui->setupUi(this);
}

OpenNewWidget::~OpenNewWidget()
{
    delete ui;
}

void OpenNewWidget::on_newFile_clicked()
{
    emit newFileClick();
//    delete (this);
}

void OpenNewWidget::on_openFile_clicked()
{
    emit openFileClick();
}

void OpenNewWidget::startSelectionRemove(){
    delete(this);
}
