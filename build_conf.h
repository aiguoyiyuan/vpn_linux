#ifndef VPN_CONF_HHH
#define VPN_CONF_HHH
#include <string>
#include <QString>

namespace base
{
char *uuid_generate ();
bool buildVPNConf(const char *id, const char *user, const char *password, const char *ip, std::string &of);
char *qs2char(QString);
}

#endif
