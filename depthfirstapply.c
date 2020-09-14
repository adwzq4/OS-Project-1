// Author: Adam Wilson
// Date: 9/14/2020
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
#include "globals.h"

// declares global Globals struct containing global variables
extern struct Globals globals;


// lists all files and sub-directories recursively, using basePath as root
int depthfirstapply(char *basePath, int_func_int pathfun) {
    char path[1000];
    char buff[100];
    struct dirent *dp;
    int k, currentLevel;
    double subtotal = 0;

    // opens directory stream starting at basePath
    DIR *dir = opendir(basePath);

    // base case of recursion occurs when unable to open directory stream
    if (!dir) {
        return 0;
    }

    // if -d is invoked, finds depth of basePath relative to depth of path on which mydu depthfirstapply()
    // was originally called
    if (globals.dflag) {
        currentLevel = globals.initialLevel * -1;
        for (k = 0; basePath[k]; k++)
            currentLevel += (basePath[k] == '/');
    }

    // reads through directory stream
    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {         

            // constructs new path from basePath
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            // prints path and size for each file if -a is invoked, accounting for -s and -d N options as well
            if (globals.aflag == 1 && globals.sflag == 0 && (globals.dflag == 0 || currentLevel + 1 <= globals.Nlevels)) {
                // if -H is true, prints size in human readable format
                if (globals.Hflag) {
                    humanReadable((double)pathfun(path), buff);
                    printf("%s     %s\n", buff, path);
                }

                // prints size in blocks, or in units according to [-b | -B M | -m] options
                else {
                    printf("%.1f %s     %s\n", pathfun(path) * globals.ratio, globals.unit, path);
                }
                
            }

            //if (!(globals.Lflag)){
            //    struct stat sb;
            //    stat(path, &sb);
            //    if (S_ISLNK(sb.st_mode)) {
            //        subtotal += pathfun(path);
            //    }
            //    else subtotal += pathfun(path) + depthfirstapply(path, sizepathfun);
            //}
            
            // recursively sums the size of each directory entry
            subtotal += pathfun(path) + depthfirstapply(path, sizepathfun);
        }
    }

    // prints path and subtotal for each directory if -s option is not invoked, accounting for -d N
    if (globals.sflag == 0 && (globals.dflag == 0 || currentLevel <= globals.Nlevels)) {
        // if -H is true, prints size in human readable format
        if (globals.Hflag) {
            humanReadable(subtotal, buff);
            printf("%s    %s\n", buff, basePath);
        }

        // prints size in blocks, or in units according to [-b | -B M | -m] options
        else {
            printf("%.1f %s     %s\n", subtotal * globals.ratio, globals.unit, basePath);
        }
    }

    closedir(dir);
    return subtotal;
}
