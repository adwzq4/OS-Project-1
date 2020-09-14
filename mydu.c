// Author: Adam Wilson
// Date: 9/14/2020

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "depthfirstapply.h"
#include "sizepathfun.h"
#include "globals.h"

// defines and initializes Globals struct with values of global variables that will effect other functions
struct Globals globals = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "blocks", 1 };

char* humanReadable(double n, char * buff);

// performs a depth first traversal of the current directory, or of all paths given as command line
// arguments, outputting total sizes and subtotals of each subdirectory
int main(int argc, char *argv[]) {
	int opt, i, j, k;
	int Msize, cflag, hflag;
	double total, grandTotal;
	char buff[100];

	total = grandTotal = Msize = cflag = hflag = 0;

	// parses through command line options
	while ((opt = getopt(argc, argv, "aB:bcd:hHLms")) != -1) {
		switch (opt) {
		case 'a':
			globals.aflag = 1;
			break;
		case 'B':
			globals.Bflag = 1;
			Msize = atoi(optarg);
			break;
		case 'b':
			globals.bflag = 1;
			break;
		case 'c':
			cflag = 1;
			break;
		case 'd':
			globals.dflag = 1;
			globals.Nlevels = atoi(optarg);
			break;
		case 'h':
			printf("Displays the sizes of all files/directories in the tree whose root is specified\
			\nin the command line.\n\n\
			-a Writes count for all files, not just directories.\n\
			-B M Scales sizes by M before printing; for example, -BM prints size in units of 1,048,576 bytes.\n\
			-b Prints size in bytes.\n\
			-c Prints a grand total.\n\
			-d N Prints the total for a directory only if it is N or fewer levels below the command line argument.\n\
			-h Prints a help message or usage, and exit\n\
			-H Prints size in human readable format, for example, 1.1KB, 234.7MB, 2.5GB.\n\
			-L Dereferences all symbolic links. By default, symbolic links are not dereferenced.\n\
			-m Equivalent to -B 1048576.\n\
			-s Displays only a total for each command line argument.");
			exit(0);
		case 'H':
			globals.Hflag = 1;
			break;
		case 'L':
			globals.Lflag = 1;
			break;
		case 'm':
			globals.mflag = 1;
			break;
		case 's':
			globals.sflag = 1;
			break;
		}
	}

	// sets unit and ratio according to [-b | -B M | -m ] options; if -B M and any others are called, -B M
	// prevails; if -m and -b are called, -m prevails over -b
	if (globals.Bflag) {
		sprintf(globals.unit, "%d-byte units", Msize);
		globals.ratio = 1. / Msize;
	}
	else if (globals.mflag){
		strcpy(globals.unit, "");
		strcat(globals.unit, "megabytes");
		globals.ratio = 1. / 1048576;
	}
	else if (globals.bflag) {
		strcpy(globals.unit, "");
		strcat(globals.unit, "bytes");
	}

	// if there are command line arguments, calls depthfirstapply() on each and outputs their total sizes
	if (optind < argc){
		for (i = optind, j = 1; i < argc; i++, j++){
			if (globals.dflag) {
				for (k = 0; argv[i][k]; k++) {
					globals.initialLevel += (argv[i][k] == '/');
				}
			}
			total = depthfirstapply(argv[i], sizepathfun);

			// if -H is true, prints total size in human readable format
			if (globals.Hflag) {
				printf("\nSize of path %d: %s\n", j, humanReadable(total, buff));
			}
			// otherwise prints size in blocks, or in units according to [-b | -B M | -m] options
			else {
				printf("\nSize of path %d: %.2f %s\n", j, total * globals.ratio, globals.unit);
			}
			grandTotal += total;
		}
	}

	// if there are no command line arguments, gives total size of current directory
	else {
		grandTotal = total = depthfirstapply(".", sizepathfun);
		if (globals.Hflag) {
			printf("\nSize of current directory: %s\n", humanReadable(total, buff));
		}
		else {
			printf("\nSize of current directory: %.2f %s\n", total * globals.ratio, globals.unit);
		}
	}

	// if -c is invoked, prints grand total size of all paths given as command line arguments
	if (cflag){
		if (globals.Hflag) {
			printf("\nGrand total memory usage: %s\n", humanReadable(grandTotal, buff));
		}
		else {
			printf("\nGrand total memory usage: %.2f %s\n", grandTotal * globals.ratio, globals.unit);
		}
	}

	return 0;
}

// takes a number of bytes and (potentially) converts it to kilobytes, megabytes, gigabytes, or terrabytes
char* humanReadable(double n, char* buff) {
	char* sizes[] = { "B", "KB", "MB", "GB", "TB" };
	int order = 0;
	while (n >= 1024 && order < 4) {
		order++;
		n /= 1024;
	}
	sprintf(buff, "%.2f %s", n, sizes[order]);
	return buff;
}
