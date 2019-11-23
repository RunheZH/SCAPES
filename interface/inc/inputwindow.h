#ifndef INPUTWINDOW_H
#define INPUTWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QThread>

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

private slots:
    void on_okayButton_clicked();

private:
    Ui::InputWindow *ui;
};

#endif // INPUTWINDOW_H
