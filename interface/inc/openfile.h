#ifndef OPENFILE_H
#define OPENFILE_H

#include <QObject>
#include <QFile>

class openfile : public QObject
{
    Q_OBJECT
public:
    explicit openfile(QObject *ui = nullptr);

signals:

public slots:
};

#endif // OPENFILE_H
