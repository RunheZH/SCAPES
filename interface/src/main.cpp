#include "../inc/mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "../../entity/stmts/inc/declIntStmt.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
