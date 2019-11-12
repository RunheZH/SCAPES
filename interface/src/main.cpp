#include "../inc/mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QSplashScreen>
#include <QTimer>
#include "../../entity/stmts/inc/declIntStmt.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    QSplashScreen* splash = new QSplashScreen();
    splash->setPixmap(QPixmap(":/imgs/interface/resource/LOGO.png"));

    splash->show();
    QTimer::singleShot(2500,splash,SLOT(close()));
    QTimer::singleShot(2500,&w,SLOT(show()));
//    w.show();

    return a.exec();
}
