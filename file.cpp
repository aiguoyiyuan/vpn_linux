#include "file.hpp"
#include <errno.h>

using namespace std;
using namespace base;

File::File(char *fn, const char *mode) :
    _handle(NULL) {
    _handle = fopen(fn, mode);
}

File::~File() {
    if (_handle != NULL) {
        fclose(_handle);
    }
}

int File::gets(string &line) {
    if (_handle == NULL)
        return -1;
    char buf[4096];
    char *s = fgets(buf, 4096-1, _handle);//file end ?
    if (s == NULL) {
        return errno;
    }
    line.assign(buf);
    return 0;
}

int File::puts(const string &line) {
    if (_handle == NULL)
        return -1;
    int ret = fputs(line.c_str(), _handle);
    if (ret == -1) {
        return errno;
    }
    return 0;
}
