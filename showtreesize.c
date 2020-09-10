#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "depthfirstapply.h"
#include "sizepathfun.h"

int main(int argc, char *argv[]) {
    char * pathname;
    struct stat statbuf;
    
    if (argc != 2){
        printf("Error: must have 1 command line argument.");
    }

    pathname = argv[1];	
	
    printf("%s  ", pathname);

    if (stat(pathname, &statbuf) == -1) {
        int err = errno;
        printf("stat() call failed: errno = %d\n", err);
        return -1;
    }
    else if (S_ISREG(statbuf.st_mode)) {
        printf("is %d bytes\n", statbuf.st_size);
    }
    else if (S_ISDIR(statbuf.st_mode)) {
        printf("is %d bytes\n", depthfirstapply(pathname, sizepathfun));
    }
    else if (S_ISCHR(statbuf.st_mode)) {
        printf("is a character device\n");
    }
    else if (S_ISBLK(statbuf.st_mode)) {
        printf("is a block device\n");
    }
    else if (S_ISFIFO(statbuf.st_mode)) {
        printf("is a pipe\n");
    }
    else if (S_ISLNK(statbuf.st_mode)) {
        printf("is a symbolic link\n");
    }
    else if (S_ISSOCK(statbuf.st_mode)) {
        printf("is a socket\n");
    }

    return 0;
}
