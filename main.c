#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "depthfirstapply.h"
#include "sizepathfun.h"

int main(int argc, char *argv[]) {
	
	char * path;	
	int opt;
	int aflag, Bflag, Msize, bflag;
	int cflag, dflag, Nlevels, hflag;
	int Hflag, Lflag, mflag, sflag;

	aflag = Bflag = Msize = bflag = 0;
	cflag = dflag = Nlevels = hflag = 0;
	Hflag = Lflag = mflag = sflag = 0;

	while ((opt = getopt(argc, argv, "aB:bcd:hHLms")) != -1) {
		switch (opt) {
		case 'a':
			aflag = 1;
			printf("a");
			break;
		case 'B':
			Bflag = 1;
			Msize = atoi(optarg);
			printf("B");
			printf("Msize: %d", Msize);
			break;
		case 'b':
			bflag = 1;
			printf("b");
			break;
		case 'c':
			cflag = 1;
			printf("c");
			break;
		case 'd':
			dflag = 1;
			Nlevels = atoi(optarg);
						printf("d");
			printf("Nlevels: %d", Nlevels);
			break;
		case 'h':
			printf("Displays the sizes of all files/directories in the tree whose root is specified\
			\nin the command line.\n\n\
			-a Write count for all files, not just directories.\n\
			-B M Scale sizes by M before printing; for example, -BM prints size in units of 1,048,576 bytes.\n\
			-b Print size in bytes.\n\
			-c Print a grand total.\n\
			-d N Print the total for a directory only if it is N or fewer levels below the command line argument.\n\
			-h Print a help message or usage, and exit\n\
			-H Human readable; print size in human readable format, for example, 1K, 234M, 2G.\n\
			-L Dereference all symbolic links. Default if to not dereference symbolic links.\n\
			-m Same as -B 1048576.\n\
			-s Display only a total for each argument.");
			exit(0);
		case 'H':
			Hflag = 1;
			printf("H");
			break;
		case 'L':
			Lflag = 1;
			printf("L");
			break;
		case 'm':
			mflag = 1;
			printf("m");
			break;
		case 's':
			sflag = 1;
			printf("s");
			break;
		}
	}

	int total = 0;
	int i;
	if (optind < argc){
		for (i = optind; i < argc; i++){
			path = argv[i];
			total = depthfirstapply(path, sizepathfun);
			if (cflag == 1){
				printf("\nGrand total memory usage = %d\n", total);
			}
		}
	}
	else {
		path = ".";
		total = depthfirstapply(path, sizepathfun);
		if (cflag == 1){
			printf("\nGrand total memory usage = %d\n", total);
		}
	}

	return 0;
}