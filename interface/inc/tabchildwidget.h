#ifndef TABCHILDWIDGET_H
#define TABCHILDWIDGET_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class tabchildwidget;
}

class tabchildwidget : public QWidget
{
    Q_OBJECT

public:
    explicit tabchildwidget(QWidget *parent = nullptr);
    void setText(QString text);
    QString getText();
    bool isEmpty();
    void clearText();
    void storeFileDir(QString dir);
    QString getFileDir();
    QString getFileName();
    void setChanged(bool changed);
    bool isChanged();
    ~tabchildwidget();

private slots:
    void on_textEdit_textChanged();

private:
    Ui::tabchildwidget *ui;
    QString fileDir;
    bool changed;
};

#endif // FILETEXT_H
