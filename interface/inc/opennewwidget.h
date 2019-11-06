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
    void startSelectionRemove();

private:
    Ui::OpenNewWidget *ui;

signals:
    void newFileClick();
    void openFileClick();
};

#endif // OPENNEWWIDGET_H
