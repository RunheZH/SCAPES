#ifndef OPENNEWWIDGET_H
#define OPENNEWWIDGET_H

#include <QWidget>

namespace Ui {
class OpenNewWidget;
}

class OpenNewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OpenNewWidget(QWidget *parent = nullptr);
    ~OpenNewWidget();

private slots:
    void on_newFile_clicked();
    void on_openFile_clicked();

private:
    Ui::OpenNewWidget *ui;
};

#endif // OPENNEWWIDGET_H
