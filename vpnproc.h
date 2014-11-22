#ifndef VPNPROC_H
#define VPNPROC_H

#include <QProcess>
#include <QString>

class VpnProc : public QProcess
{
    Q_OBJECT
public:
    explicit VpnProc(QObject *parent = 0);

signals:
    void setVPNInfo(bool state, QString message);
public slots:
    void startVPN(QString id, QString user, QString password, QString ip);
};

#endif // VPNPROC_H
