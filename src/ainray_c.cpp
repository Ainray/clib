//#include"stdafx.h"
#pragma warning(disable:4996)

//deretives above are special for VS (Windows)

#include "ainray_c.h"
#include<stdio.h>
#include<stdarg.h>
#include<string.h>

#define HYPHEN '\\'
#define SHYPHEN "\\"

// concatenate path independent on platforms
// input: mode, indicate file(1) or path(0)
//        fullpath, char array to contained the full path
//        n, number of parts, at least 1
//      ..., parts list with type of (char *)
// return: pointer to the fullpath or NULL (indicate error)
char* path_cat(int mode, char *fullpath, int n, ...)
{
	// check input arguments
	if (fullpath == NULL || n < 1)
		return NULL;

	// deal with input argument list
	char *spath;
	va_list ap;
	va_start(ap, n);
	for (int i = 0; i < n; ++i) {
		spath = va_arg(ap, char *);
		int len = (int)strlen(spath);

		// remove tailing "/" or "\" when necessary
		if (*(spath + len - 1) == HYPHEN)
			*(spath + len - 1) = '\0';

		if (i == 0) {//first parts, need no prefixed "\" or "/"
			strcpy(fullpath, spath);
		}
		else {
			strcat(fullpath, SHYPHEN);
			strcat(fullpath, spath);
		}
	}
	if (mode == 0) //for path, add tailing "\" or "/" for path
		strcat(fullpath, SHYPHEN);
	va_end(ap);

	return fullpath;
}