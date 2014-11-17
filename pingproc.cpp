#include "pingproc.h"
#include <define.h>
#include <QDebug>

using namespace std;
using namespace base;

PingProc::PingProc(QObject *parent) :
    QProcess(parent)
{
}

void PingProc::getping(QString area, QString ip, int line)
{
    QString cmd("ping");
    QStringList args;
    args << ip << PING_ARGS.c_str();
    QProcess::ProcessState s = state();
    qDebug() << "state: " << s;
    start(cmd, args);
    bool ret = waitForFinished(1000);
    if (ret == false) {
        closeReadChannel(QProcess::StandardOutput);
        closeReadChannel(QProcess::StandardError);
        setProcessState(QProcess::NotRunning);
    }
    QString sec;
    QString result;
    int from, b, e;

    if (ret == false) {
        sec.setNum(200);
            //emit setPingping(_currentLine, sec);
    } else {
        result = QString::fromLocal8Bit(readAllStandardOutput());
        from = result.indexOf(QString("mdev"));
        if (from == -1) {
            sec.setNum(200);
                //emit setPingping(_currentLine, sec);
        }
        b = result.indexOf('/', from);
        if (b == -1) {
            sec.setNum(200);
                //emit setPingping(_currentLine, sec);
        }
        e = result.indexOf('/', b+1);
        if (e == -1) {
             sec.setNum(200);
                //emit setPingping(_currentLine, sec);
        }
        sec =  result.mid(b+1, e-b-1);
            //emit setPingping(_currentLine, sec);
    }
    //QDebug qDebug;
    qDebug() << ip << sec;
    emit setping(area, sec, line);
}
