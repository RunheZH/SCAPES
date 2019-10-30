#ifndef TABCHILDWIDGET_H
#define TABCHILDWIDGET_H

#include <QWidget>

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
    ~tabchildwidget();

private:
    Ui::tabchildwidget *ui;
    QString fileDir;
};

#endif // FILETEXT_H
