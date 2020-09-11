// References: https://codeforwin.org/2018/03/c-program-to-list-all-files-in-a-directory-recursively.html#:~:text=Open%20directory%20stream%20using%20opendir,%2C%20using%20dp%2D%3Ename%20.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "depthfirstapply.h"
#include "sizepathfun.h"

// global variables which affect the ouput of depthfirstapply
extern int aflag, sflag;
extern char unit[100];
extern double ratio;

/**
 * Lists all files and sub-directories recursively 
 * considering path as base path.
 */
int depthfirstapply(char *basePath, int_func_int pathfun) {
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    // base case of recursion occurs when unable to open directory stream
    if (!dir) {
        return 0;
    }

    int subtotal = 0;


    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {         

            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            // prints path and size for each file if -a is invoked
            if (aflag == 1 && sflag == 0) {
                printf("%s    %.1f %s\n", path, pathfun(path) * ratio, unit);
            }

            // recursively sums the size of each directory entry
            subtotal += pathfun(path) + depthfirstapply(path, sizepathfun);
        }
    }

    // prints path and subtotal for each directory if -s option is not invoked
    if (sflag == 0) {
        printf("%s    %.1f %s\n", basePath, subtotal * ratio, unit);
    }

    closedir(dir);
    return subtotal;
}
