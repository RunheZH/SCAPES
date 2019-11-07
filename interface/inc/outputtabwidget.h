#ifndef OUTPUTTABWIDGET_H
#define OUTPUTTABWIDGET_H

#include <QWidget>

namespace Ui {
class OutputTabWidget;
}

class OutputTabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OutputTabWidget(QWidget *parent = nullptr);
    void tabSetName(QString tabName);
    void setText(QString text);
    void addText(QString text);
    void clearText();
    QString getTabName();
    ~OutputTabWidget();

private:
    Ui::OutputTabWidget *ui;
    QString tabName;
};

#endif // OUTPUTTABWIDGET_H
