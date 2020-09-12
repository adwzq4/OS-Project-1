#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "sizepathfun.h"

extern int Lflag;

int sizepathfun(char* path) {
    struct stat statbuf;

    if (Lflag) {
        stat(path, &statbuf);
        return statbuf.st_blocks;
    }
    else {
        lstat(path, &statbuf);
        return statbuf.st_blocks;
    }
}
