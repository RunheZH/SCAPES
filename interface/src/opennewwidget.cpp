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

}

void OpenNewWidget::on_openFile_clicked()
{

}
