#pragma once
#include <string.h>
#include <errno.h>
#include <stdio.h>

//------------------------ file and line where error occurs --------------------------------
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
// full file name

#ifdef _DEBUG
#define FILEINFO "(" __FILE__ ":" TOSTRING(__LINE__) ")"
#else
#define FILEINFO "error"
#endif
#define ERROR_BUFLEN	1024

const char *geterrorinfo();
void seterrorinfo(const char *s);
int getlasterrorno();
void seterrorno(int errno);
