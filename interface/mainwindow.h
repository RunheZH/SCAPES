#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
//#include <QtCore>
//#include <QtGui>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void compileText(QString text);
    ~MainWindow();

private slots:
    void on_actionAbout_SCAPES_triggered();
    void on_actionQuit_triggered();
    void on_actionSave_triggered();
    void on_actionOpen_triggered();
    void on_dirView_doubleClicked(const QModelIndex &index);

    void on_actionNew_triggered();

    void on_actionCompile_triggered();

private:
    Ui::MainWindow *ui;
    QString currentFile = "";
    QFileSystemModel *dirmodel;
    void dirView();
    void openFile();
    void openFile(const QModelIndex &index);
    void saveFile();
};

#endif // MAINWINDOW_H
