#ifndef FILE_HHH
#include <stdio.h>
#include <string>

namespace base
{

class File
{
private:
    FILE *_handle;

public:
    File(char *fn, const char *mode);
    ~File();
    int gets(std::string &line);
    int puts(const std::string &line);
};

}
#endif
