#include "linelist.hpp"
#include <string>
#include <map>
#include <vector>
#include "file.hpp"
#include <string.h>

using namespace base;
using namespace std;

string trim(const string &s, const char *c) {
    vector<char> cs;
    int i=0;
    while (i<strlen(c)) {
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

vector<string> splitString(const string &s, const char sp) {
    vector<string> vs;
    size_t b = 0;
    size_t p = 0;
    for (p = 0; p<s.size(); p++) {
        if (s[p] == sp) {
            vs.push_back(s.substr(b, p-b));
            b = p+1;
        }
    }
    vs.push_back(s.substr(b, p-b));
    return vs;
}

//LineItem::LineItem(const string &name, const string &ip, const std::vector<string> protocols, const string &area) :
LineItem::LineItem(const string &id, const string &name, const string &ip, const string &protocols, const string &area) :
    _id(id), _name(name), _ip(ip), _protocols(protocols), _area(area)
{
}

LineItem::LineItem()
{
}

string LineItem::getId() {
    return _id;
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

//LineList::LineList()
//{
//}

int LineList::initFromFile(const string &fn) {
    File file(fn.c_str(), "r");
    string line;

    enum Status{NONE, SECTION, DATA};
    Status status=NONE;

    string id, name, ip, area;
    //vector<string> protocols;
    string protocols;
    int ret = 0;
    size_t len = 0;
    string section;
    int debug=0;
    while((ret = file.gets(line)) == 0) {
        line = trim(line, " \r\n");
        len = line.size();
        if (len == 0 || line[0] == '#') {
            continue;
        }

        if (status == NONE) {
            if (len > 2 && line[0] == '[' && line[len-1]==']') {
                section = trim(line, " []");
                if (section == "line") {
                    status = DATA;
                }
            }
            continue;
        }

        if (status == DATA) {
            if (len > 2 && line[0] == '[' && line[len-1]==']') {
                section = trim(line, " []");
                if (section == "line") {
                    status = SECTION;
                } else {
                    status = NONE;
                }
            } else {
                vector<string> datas;
                datas = splitString(line, '=');
                if (datas.size() != 2)
                    continue;
                string key = trim(datas[0], " ");
                if (key == "id") {
                    id = trim(datas[1], " \"");
                } else if (key == "name") {
                    name = trim(datas[1], " \"");
                } else if (key == "ip") {
                    ip = trim(datas[1], " \"");
                } else if (key == "protocol") {
                    protocols = trim(datas[1], " \"");
                } else if (key == "area") {
                    area = trim(datas[1], " \"");
                }
            }
        }

        if (status != DATA) {
            if (name.size() > 0 && ip.size() > 0 &&
                    protocols.size() > 0 && area.size() > 0) {
                LineItem item(id, name, ip, protocols, area);
                if (_list.find(area) != _list.end()) {
                    _list[area].push_back(item);
                } else {
                    vector<LineItem> e;
                    e.push_back(item);
                    _list.insert(make_pair(area, e));
                }
            }
            name.clear();
            ip.clear();
            protocols.clear();
            area.clear();
            if (status == SECTION)
                status = DATA;
        }
    }
    if (status == DATA && name.size() > 0 && ip.size() > 0 &&
            protocols.size() > 0 && area.size() > 0) {
        LineItem item(id, name, ip, protocols, area);
        if (_list.find(area) != _list.end()) {
            _list[area].push_back(item);
        } else {
            vector<LineItem> e;
            e.push_back(item);
            _list.insert(make_pair(area, e));
        }
    }
    if (ret == -1) {
        return 0;
    }
    return -1;
}

vector<LineItem> LineList::getLineByArea(const string &area) {
    if (_list.find(area) != _list.end()) {
        return _list[area];
    } else {
        return vector<LineItem>();
    }
}
