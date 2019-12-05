#ifndef INPUTWINDOW_H
#define INPUTWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QThread>
#include <QEventLoop>
#include <QIntValidator>

namespace Ui {
class InputWindow;
}

class InputWindow : public QWidget
{
    Q_OBJECT

public:
    explicit InputWindow(QWidget *parent = nullptr);
    int readValue(QString variableName);
    ~InputWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_okayButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::InputWindow *ui;
    int whichClicked = 0;   //okay button clicked = 1, cancel button clicked = 0

signals:
    void okayClicked();
    void cancelClicked();
    void windowClose();
};

#endif // INPUTWINDOW_H
