#ifndef DEPTHFIRSTAPPLY_H
#define DEPTHFIRSTAPPLY_H

int depthfirstapply(char* path, int pathfun(char* path1));
typedef int (*int_func_int) (char*);

#endif