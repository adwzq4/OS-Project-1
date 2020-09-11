// References: https://codeforwin.org/2018/03/c-program-to-list-all-files-in-a-directory-recursively.html#:~:text=Open%20directory%20stream%20using%20opendir,%2C%20using%20dp%2D%3Ename%20.

#include <stdio.h>
#include <string.h>
<<<<<<< HEAD
#include <stdlib.h>
=======
>>>>>>> 1daada6b00b05e4d982addcac82eb8c2de8f50c0
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "depthfirstapply.h"
#include "sizepathfun.h"

<<<<<<< HEAD
// global variables which affect the ouput of depthfirstapply
extern int aflag, sflag;
extern char unit[100];
extern double ratio;

=======
>>>>>>> 1daada6b00b05e4d982addcac82eb8c2de8f50c0
/**
 * Lists all files and sub-directories recursively 
 * considering path as base path.
 */
<<<<<<< HEAD
int depthfirstapply(char *basePath, int_func_int pathfun) {
=======
int depthfirstapply(char *basePath, int_func_int pathfun)
{
>>>>>>> 1daada6b00b05e4d982addcac82eb8c2de8f50c0
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

<<<<<<< HEAD
    // base case of recursion occurs when unable to open directory stream
    if (!dir) {
        return 0;
    }

    int subtotal = 0;


    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {         
=======
    // Unable to open directory stream
    if (!dir)
        return 0;

    int sum = 0;
    int pathfunResult = 0;
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
<<<<<<< HEAD
            //printf("\n%-20s\t\t", dp->d_name);            
=======
            printf("\n%-20s\t\t", dp->d_name);            
>>>>>>> b1a25d7ac8fdd30b4e81925a153c94528791709d
>>>>>>> 1daada6b00b05e4d982addcac82eb8c2de8f50c0

            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
<<<<<<< HEAD

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
=======
<<<<<<< HEAD
	        pathfunResult = pathfun(path);
=======
	    pathfunResult = pathfun(path);
>>>>>>> b1a25d7ac8fdd30b4e81925a153c94528791709d
            if (pathfunResult >= 0) {
                sum += pathfunResult + depthfirstapply(path, sizepathfun);
            }
            else sum += depthfirstapply(path, sizepathfun);

        }
    }

    closedir(dir);
    return sum;
>>>>>>> 1daada6b00b05e4d982addcac82eb8c2de8f50c0
}
