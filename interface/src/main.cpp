#include "../inc/mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "../../entity/stmts/inc/declIntStmt.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

      QString str1 = "dci a";
      QString str2 = "rdi a";

      Statement* temp1 = new DeclIntStmt("fileName", str1, nullptr);
      //Statement* temp2 = new DeclIntStmt("fileName", str2, nullptr);

      qDebug() << "First Test";
      qDebug() << temp1->compile();

      //qDebug() << "Second Test";
      //qDebug() << temp2->compile();


    return a.exec();
}
