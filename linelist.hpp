#ifndef LINELIST_HHH
#define LINELIST_HHH

namespace base

class LineItem
{
private:
    std::string _name;
    std::string _ip;

class LineList
{
private:
    std::map<std::string, std::vector<LineItem> > _list;
    int readFromFile(const std::string &fn);
    std::vector<LineItem> getLIneByArea(const string &area);
};

}
#endif
