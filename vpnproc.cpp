#include "vpnproc.h"
#include "build_conf.h"
#include <sys/stat.h>
#include <string>
#include "build_conf.h"

using namespace std;
using namespace base;

VpnProc::VpnProc(QObject *parent) :
    QProcess(parent)
{
}

void VpnProc::startVPN(QString id, QString user, QString password, QString ip)
{
    string ofile;
    QString message;
    bool state = false;
    QString cmd("nmcli");
    QStringList args;
    int code;
    char *c_id = qs2char(id);
    char *c_user = qs2char(user);
    char *c_ps = qs2char(password);
    char * c_ip = qs2char(ip);

    bool ret = buildVPNConf(c_id, c_user, c_ps, c_ip, ofile);
    if (ret == false) {
        message.append("build vpn conf file error");
        goto EMIT_INFO;
    }

    if (chmod(ofile.c_str(), S_IRUSR) != 0) {
        message.append("chmod error");
        goto EMIT_INFO;
    }

    args << "con up id" << id;
    start(cmd, args);
    ret = waitForFinished(30000);
    if (ret != true) {
        message.append("excute nmcli error");
        goto EMIT_INFO;
    }
    code = exitCode();
    if (code != 0) {
        message.append("nmclie error return ");
    }
    state = true;
EMIT_INFO:
    emit setVPNInfo(state, message);
}
