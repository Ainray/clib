/* C interface lib
author: Ainray
email: wwzhang0421@163.com
create date: 2020 04 28
last modified date: 2020 04 28
					2020 07 31, add some functions
*/

#ifndef AINRAY_C_H
#define AINRAY_C_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#include<string.h>
#include<ctype.h>

#define TRUE 1
#define FALSE 0

#ifdef _WIN32_
#pragma warning(disable:4996) //special for VS (Windows)
#pragma warning(disable:4312)
#pragma warning(disable:4302)
#pragma warning(disable:4311)
#endif

#define PATH_HYPHEN_DOS '\\'
#define PATH_HYPHEN_UNIX '/'
#define PATH_SHYPHEN_DOS "\\"
#define PATH_SHYPHEN_UNIX "/"

#ifdef _WIN32_
#define PATH_HYPHEN PATH_HYPHEN_DOS
#define PATH_SHYPHEN PATH_SHYPHEN_DOS
#else //unix
#define PATH_HYPHEN PATH_HYPHEN_UNIX
#define PATH_SHYPHEN PATH_SHYPHEN_UNIX
#endif
// ---------------- math operation ------------------

//example: average(x, 10, 0, 10)
//         average(x, 10, 0, 3);
//         average(x, 10, 2, 3);
double average(double *x, int len, int offset, int n);


// ---------------- path operation ------------------

// concatenate path independent on platforms
// input: mode, indicate file(1) or path(0)
//        fullpath, char array to contained the full path
//        n, number of parts, at least 1
//      ..., parts list with type of (char *)
// return: pointer to the fullpath or NULL (indicate error)
char* path_cat(int mode, char *fullpath, int n, ...);

// concatenate path independent on platforms, with double null terminals, and normal null is used as
// seperator, especially for path operation by using SHFileOperation
char * path_catwithdzt(char *dst, int len, int n, ...);

// compact continous path hyphens, such as "//" or "\/" or "////" and etc.
char *path_compact(char *path);

//convert "\\" into "/"
char *path_d2u(char *path);
//convert "/" into "\\"
char *path_u2d(char *path);

#ifdef _WIN32_ //unifying unix and dos format
#define PATH_UDC path_u2d
#else
#define PATH_UDC path_d2u
#endif // _WIN32_



char* path_getdirectory(char *dir, int n, char *path);

//get filename from path
char * path_getfilename(char *fname, int n, char *path);

char * path_getfilenamewithoutext(char *purefname, int n, char *path);

// ----------------- string operation ----------------------

int stra2i(char *s, int len);

// copy string safely
// dst, it is assumed to has enough spapce
// src, if src has length < len - 1, then zero is padded to to dst; 
//      if src has length >= len - 1, then no zero is added at then end of dst
//      anyway, padding zero manually, then the source string is truncated, 
//      which is resonable because it results from non-enough space in dst
// 
// exampel: strcopy(dst, len, src, len);
char * strcopy(char *dst, int len, char *src, int n);

char * straddprefix(char *dst, int nd, char *src, int ns, char *prefix, int np);
void strappendfile(FILE *pfile, char *s);
char * strtruncprefix(char *str, int n, char *prefix);
char * strrtrim(char *src, char *pat);
char *strrtrim(char *src, int pat);

// --------------- system utilities ------------
char *mem_hexdump(char *buf, int len, int width, long addr, int size);
#endif
