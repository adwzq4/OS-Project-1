// Author: Adam Wilson
// Date: 9/14/2020

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "sizepathfun.h"
#include "globals.h"

// declares global Globals struct of global variables
extern struct Globals globals;

// returns the size of the directory entry indicated by path
int sizepathfun(char* path) {
    struct stat statbuf;

    // if any of the options affecting unit of size are invoked, size is returned in bytes
    if (globals.Hflag + globals.bflag + globals.Bflag + globals.mflag > 0) {
        // if -L is selected, symbolic links are dereferenced, returning the size
        // of what the symbolic link is pointing to
        if (globals.Lflag) {
            // if stat() call fails, calls perror and exits program
            if (stat(path, &statbuf) == -1) {
                perror("Error ");
                exit(-1);
            }
            else return statbuf.st_size;
        }
        // otherwise, symbolic links are not dereferenced (size is that of the link itself) 
        else {
            if (lstat(path, &statbuf) == -1) {
                perror("Error ");
                exit(-1);
            }
            else return statbuf.st_size;
        }
    }

    // otherwise, size is returned in units of 512-byte blocks, accounting for -L option
    if (globals.Lflag) {
        if (stat(path, &statbuf) == -1) {
            perror("Error ");
            exit(-1);
        }
        else return statbuf.st_blocks;
    }
    else {
        if (lstat(path, &statbuf) == -1) {
            perror("Error ");
            exit(-1);
        }
        else return statbuf.st_blocks;
    }
}
