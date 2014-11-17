#ifndef PINGPROC_H
#define PINGPROC_H

#include <QObject>
#include <QProcess>
#include <QString>
#include <vector>
#include <linelist.hpp>

class PingProc : public QProcess
{
    Q_OBJECT
public:
    explicit PingProc(QObject *parent = 0);

signals:
    void setping(QString area, QString ip, int line);

public slots:
    void getping(QString area, QString ip, int line);
};

#endif // PINGPROC_H
