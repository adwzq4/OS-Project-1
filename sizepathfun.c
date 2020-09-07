#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "sizepathfun.h"

int sizepathfun(char* path) {
    struct stat statbuf;
    if (stat(path, &statbuf) == -1) {
        int err = errno;
        printf("-1     stat() call failed: errno = %d", err);
        return -1;
    }
    else {
        printf("%d", statbuf.st_size);
        return statbuf.st_size;
    }
}
