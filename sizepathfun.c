#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "sizepathfun.h"

int sizepathfun(char* path) {
    struct stat statbuf;
    if (stat(path, &statbuf) == -1) {
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 1daada6b00b05e4d982addcac82eb8c2de8f50c0
        //int err = errno;
        //printf("-1     stat() call failed: errno = %d", err);
        return -1;
    }
    else {
	    //printf("%d", statbuf.st_blocks);
        return statbuf.st_blocks;
<<<<<<< HEAD
=======
=======
        int err = errno;
        printf("-1     stat() call failed: errno = %d", err);
        return -1;
    }
    else {
        printf("%d", statbuf.st_size);
        return statbuf.st_size;
>>>>>>> b1a25d7ac8fdd30b4e81925a153c94528791709d
>>>>>>> 1daada6b00b05e4d982addcac82eb8c2de8f50c0
    }
}
