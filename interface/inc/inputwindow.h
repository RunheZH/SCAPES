#ifndef INPUTWINDOW_H
#define INPUTWINDOW_H

#include <QWidget>

namespace Ui {
class InputWindow;
}

class InputWindow : public QWidget
{
    Q_OBJECT

public:
    explicit InputWindow(QWidget *parent = nullptr);
    ~InputWindow();

private:
    Ui::InputWindow *ui;
};

#endif // INPUTWINDOW_H
