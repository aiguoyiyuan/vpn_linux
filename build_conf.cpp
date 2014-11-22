#include "build_conf.h"
#include <file.hpp>
#include <define.h>
#include <string>
#include <uuid/uuid.h>
#include <stdlib.h>
#include <QDebug>
#include <QString>
#include <QByteArray>

using namespace std;

namespace base {

char *uuid_generate ()
{
    uuid_t uuid;
    char *buf;

    buf = (char*)malloc(37);
    uuid_generate_random (uuid);
    uuid_unparse_lower (uuid, &buf[0]);
    return buf; 
}

bool buildVPNConf(const char *id, const char *user, const char *password, const char *ip, string &of)
{
    File file(VPN_CONF.c_str(), "r");
    string buf;
    if (file.readAll(buf) != 0) {
        //write log
        return false;
    }

    char *uuid = uuid_generate();
    char vpn_config[4096]={0};
    int len = snprintf(vpn_config, 4096, buf.c_str(), id, uuid, ip, user, password);
    free(uuid);

    string ofile(VPN_CONF_PATH+id);
    File out(ofile.c_str(), "w");
    int ret;
    qDebug() << ofile.c_str();
    qDebug() << vpn_config;
    if ((ret = out.puts(string(vpn_config))) != len) {
        return false;
    }
    of.assign(ofile);
    return true;
}

char *qs2char(QString s)
{
    QByteArray ba = s.toLatin1();
    return ba.data();
}

}
