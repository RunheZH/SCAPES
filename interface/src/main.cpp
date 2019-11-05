#include "../inc/mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "../../entity/stmts/inc/declIntStmt.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

      QString str = "jmr L1";
      Statement* temp = new DeclIntStmt("fileName", str, nullptr);
      qDebug() << temp->compile();
      qDebug() << "look up";


    return a.exec();
}
