#include "file.hpp"
#include <errno.h>

using namespace std;
using namespace base;

File::File(const char *fn, const char *mode) :
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
        return -2;
    char buf[4096];
    char *s = fgets(buf, 4096-1, _handle);//file end ?
    if (s == NULL) {
        if (feof(_handle) != 0) {
            return -1;
        }
        return errno;
    }
    line.assign(buf);
    return 0;
}

int File::puts(const string &line) {
    if (_handle == NULL)
        return -2;
    int ret = fputs(line.c_str(), _handle);
    if (ret <= 0) {
        return errno;
    }
    return ret;
}
