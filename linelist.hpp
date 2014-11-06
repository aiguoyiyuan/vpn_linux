#ifndef LINELIST_HHH
#define LINELIST_HHH
#include <string>
#include <map>
#include <vector>

namespace base

class LineItem
{
private:
    std::string _name;
    std::string _ip;
    std::vector<std::string> _protocols;
    std::string _area;

public:
    LineItem();
    LineItem(const std::string &name, const std::string &ip,
             const std::vector<std::string> protocols, const std::string &area);
    std::string getName();
    std::string getIp();
    std::vector<std::string> getProtocols();
    std::string getArea();
};

class LineList
{
private:
    std::map<std::string, std::vector<LineItem> > _list;

public:
    LineList();
    ~LineList();
    int initFromFile(const std::string &fn);
    std::vector<LineItem> getLineByArea(const string &area);
};

}
#endif
