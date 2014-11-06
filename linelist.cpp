#include "linelist.hpp"
#include <string>
#include <map>
#include <vector>
#include "file.hpp"

using namespace base;
using namespace std;

string trim(const string &s, char *c) {
    vector<char> cs;
    int i=0;
    while (i<len(c)) {
        cs.push_back(c[i]);
        i++;
    }

    size_t b=0, e=s.size();
    while (b < e) {
        int ob = b;
        for (size_t p=0;p<cs.size();p++) {
            if (s[b] == cs[p]) {
                b++;
                break;
            }
        }
        if (b == ob) {
            break;
        }
    }

    e--;
    while (e > b) {
        int oe = e;
        for (size_t p=0;p<cs.size();p++) {
            if (s[e] == cs[p]) {
                e--;
                break;
            }
        }
        if (e == oe) {
            break;
        }
    }

    return s.substr(b, e-b+1);
}

vector<string> splitString(const string &s, char sp) {
    vector<string> vs;
    size_t b = 0;
    for (size_t p = 0; p<s.size(); p++) {
        if (s[p] == sp) {
            vs.append(s.substr(b, p-b));
            b = p+1;
        }
    }
    vs.append(b, p-b);
}

LineItem::LineItem(const string &name, const string &ip, const std::vector<string> protocols, const string &area) :
    _name(name), _ip(ip), _protocols(protocols), _area(area)
{
}

LineItem()
{
}

string LineItem::getName() {
    return _name;
}

string LineItem::getIp() {
    return _ip;
}

string LineItem::getProtocols() {
    return _protocols;
}

string LineItem::getArea() {
    return _area;
}

LineList::LineList()
{
}

int LineList::initFromFile(const string &fn) {
    File file(fn.c_str(), "r");
    string line;

    enum Status{NONE, SECTION, DATA};
    Status status=NONE;

    string name, ip, area;
    vector<string> protocols;
    int ret = 0;
    size_t len = 0;
    while((ret = file.gets(line)) == 0) {
        line = trim(line, " \r\n");
        len = line.size();
        if (len == 0 || line[0] == '#') {
            continue;
        }

        if (status == NONE) {
            if (len > 2 && line[0] == '[' && line[len-1]==']') {
                section = trim(line, " []");
                if (section == 'line') {
                    status == DATA;
                }
            }
            continue;
        }

        if (status == DATA) {
            if (len > 2 && line[0] == '[' && line[len-1]==']') {
                section = trim(line, " []");
                if (section == 'line') {
                    status == SECTION;
                } else {
                    status == NONE;
                }
            } else {
                vector<string> datas;
                datas = splitString(line, '=');
                if (datas.size() != 2)
                    continue;
                string key = trim(datas[0], " ");
                if (key == "name") {
                    name = trim(datas[1], " \"");
                } else if (key == "ip") {
                    ip = trim(datas[1], " \"");
                } else if (key == "protocol") {
                    protocols = splitString(trim(datas[1], " \""), '+');
                } else if (key == "area") {
                    area = trim(datas[1], " \"");
                }
            }
        }

        if (status != DATA) {
            if (name.size() > 0 && ip.size() > 0 &&
                    protocols.size() > 0 && area.size() > 0) {
                LineItem item(name, ip, protocols, area);
                if (_list.find(area) != _list.end()) {
                    _list[area].push_back(item);
                } else {
                    vector<string> e;
                    e.push_back(item);
                    _list.insert(make_pair(area, e));
                }
            }
            name.clear();
            ip.clear();
            protocols.clear();
            area.clear();
            if (statsu == SECTION)
                status = DATA;
        }
    }
}
