#ifndef TABCHILDWIDGET_H
#define TABCHILDWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QRegExp>
#include <QRegExpValidator>
#include <QRegularExpressionMatch>
#include <QScrollBar>

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
    void storeFilePath(QString dir);
    QString getFilePath();
    QString getFileName();
    QString getFileType();
    void setChanged(bool changed);
    bool isChanged();
    ~tabchildwidget();

private slots:
    void on_textEdit_textChanged();
    void updateScroll(int pos);

signals:
    void textChange();
    void sliderMoved(int);

private:
    Ui::tabchildwidget *ui;
    QString filePath = "";
    QString fileName = "";
    QString fileType;   //scp,jsn
    bool changed = false;
    int getLineNum();
    void updateLineNum();
    void setFileType();
};

#endif // FILETEXT_H
