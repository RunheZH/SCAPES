#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QDebug>
//#include <QtCore>
//#include <QtGui>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QPair>
#include <QVector>
#include <QDir>
#include <QCloseEvent>
#include <QStandardPaths>
#include "tabchildwidget.h"
#include "opennewwidget.h"
#include "outputtabwidget.h"
#include "../../control/inc/compileControl.h"
#include "../../control/inc/saveControl.h"
#include "../../control/inc/runControl.h"
#include "../../entity/inc/program.h"
#include "../inc/inputwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    QVector<QPair<QString , Program*>> programList;    //vector<pair<String fileName, Program* pgm>> programList
    void outToConsole(QString errorText);
    void outToError(QString consoleText);
    ~MainWindow()  override;

protected:
    void closeEvent(QCloseEvent*) override;

private:
    Ui::MainWindow *ui;
    QString currentFile = "";
    OpenNewWidget* onw;
    QFileSystemModel *dirmodel;
    OutputTabWidget* consoleTab;
    OutputTabWidget* errorTab;
    void startSelectionView();
    void outputView();
    void dirView();
    void dirUpdate(QString filePath);
    int openFile();
    void openFile(const QModelIndex &index);
    int saveAsFile();
    void saveFile();
    void compileText(QString filePath);
    void runText(QString filePath);
    void tabView();
    void tabAdd();
    int tabIsExist(QString fileDir);

private slots:
    void startNewView();
    void startOpenView();
    void on_actionAbout_SCAPES_triggered();
    void on_actionQuit_triggered();
    void on_actionSave_triggered();
    void on_actionOpen_triggered();
    void on_dirView_doubleClicked(const QModelIndex &index);

    void on_actionNew_triggered();

    void on_actionCompile_triggered();

    void on_actionRun_triggered();

    void on_tabWidget_tabCloseRequested(int index);
    void on_tabWidget_tabBarClicked(int index);
    void on_actionSave_As_triggered();

 signals:
    void startSelectionRemove();
};

#endif // MAINWINDOW_H
