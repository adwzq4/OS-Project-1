// References: https://codeforwin.org/2018/03/c-program-to-list-all-files-in-a-directory-recursively.html#:~:text=Open%20directory%20stream%20using%20opendir,%2C%20using%20dp%2D%3Ename%20.

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int depthfirstapply(char *path, int pathfun(char *path1));
int sizepathfun(char *path);
typedef int (*int_func_int) (char*);


int main()
{
    // Directory path to list files
    char path[100];

    // Input path from user
    printf("Enter path to list files: ");
    scanf("%s", path);

    //printf("%d\n", sizepathfun(path));
    int total = depthfirstapply(path, sizepathfun);
    printf("\ntotal = %d\n", total);
    return 0;
}


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
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            printf("\n%s\t", dp->d_name);
            printf("%d", pathfun(dp->d_name));

            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
            sum += pathfun(dp->d_name) + depthfirstapply(path, sizepathfun);
        }
    }

    closedir(dir);
    return sum;
}

int sizepathfun(char *path){
    struct stat statbuf;
    if (stat(path, &statbuf) != -1){
        return statbuf.st_size;
    }
    else return -1;
}
