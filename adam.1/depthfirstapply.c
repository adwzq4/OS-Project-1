// References: https://codeforwin.org/2018/03/c-program-to-list-all-files-in-a-directory-recursively.html#:~:text=Open%20directory%20stream%20using%20opendir,%2C%20using%20dp%2D%3Ename%20.

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "depthfirstapply.h"
#include "sizepathfun.h"

/**
 * Lists all files and sub-directories recursively 
 * considering path as base path.
 */
int depthfirstapply(char *basePath, int_func_int pathfun)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    // Unable to open directory stream
    if (!dir)
        return 0;

    int sum = 0;
    int pathfunResult = 0;
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            //printf("\n%-20s\t\t", dp->d_name);            

            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
	        pathfunResult = pathfun(path);
            if (pathfunResult >= 0) {
                sum += pathfunResult + depthfirstapply(path, sizepathfun);
            }
            else sum += depthfirstapply(path, sizepathfun);

        }
    }

    closedir(dir);
    return sum;
}
