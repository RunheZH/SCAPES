#include "../inc/mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    QSplashScreen* splash = new QSplashScreen();
    splash->setPixmap(QPixmap(":/imgs/imgs/LOGO.png"));

    //uncomment this to show logo
//    splash->show();
//    QTimer::singleShot(2500,splash,SLOT(close()));
//    QTimer::singleShot(2500,&w,SLOT(show()));

    //uncomment this to not show logo
    w.show();

    return a.exec();
}
