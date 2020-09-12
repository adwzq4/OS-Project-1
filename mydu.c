#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "depthfirstapply.h"
#include "sizepathfun.h"

int aflag, sflag, Lflag, initialLevel, dflag, Nlevels, Hflag;
char unit[100] = { };
double ratio;

int main(int argc, char *argv[]) {
	int opt, i, j, k;
	int Bflag, Msize, bflag, cflag, mflag, hflag;
	double total, grandTotal;

	strcat(unit, "blocks");
	ratio = 1;
	total = grandTotal = 0;
	aflag = Bflag = Msize = bflag = Hflag = Lflag = 0;
	cflag = dflag = Nlevels = hflag = mflag = sflag = 0;
	initialLevel = 0;

	while ((opt = getopt(argc, argv, "aB:bcd:hHLms")) != -1) {
		switch (opt) {
		case 'a':
			aflag = 1;
			break;
		case 'B':
			Bflag = 1;
			Msize = atoi(optarg);
			break;
		case 'b':
			bflag = 1;
			break;
		case 'c':
			cflag = 1;
			break;
		case 'd':
			dflag = 1;
			Nlevels = atoi(optarg);
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
			break;
		case 'L':
			Lflag = 1;
			break;
		case 'm':
			mflag = 1;
			break;
		case 's':
			sflag = 1;
			break;
		}
	}

	if (bflag + mflag + Bflag > 1) {
		printf("Error: At most one of the options -b, -m, and -B may be invoked at once.");
		exit(1);
	}

	if (bflag){
		strcpy(unit, "");
		strcat(unit, "bytes");
		ratio = 512;
	}
	else if (mflag){
		strcpy(unit, "");
		strcat(unit, "megabytes");
		ratio = 512. / 1048576;
	}
	else if (Bflag){
		sprintf(unit, "%d-byte units", Msize);
		ratio = 512. / Msize;
	}

	if (optind < argc){
		for (i = optind, j = 1; i < argc; i++, j++){
			if (dflag) {
				for (k = 0; argv[i][k]; k++)
					initialLevel += (argv[i][k] == '/');
			}
			total = depthfirstapply(argv[i], sizepathfun) * ratio;
			printf("\nSize of path %d: %.2f %s\n", j, total, unit);
			grandTotal += total;
		}
	}
	else {
		grandTotal = total = depthfirstapply(".", sizepathfun) * ratio;
		printf("\nSize of current directory: %.2f %s\n", total, unit);
	}

	if (cflag){
		printf("Grand total memory usage: %d %s", grandTotal, unit);
	}

	return 0;
}
