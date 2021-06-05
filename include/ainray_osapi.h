/* Win32 interface lib for C program in Windows

author: Ainray
email: wwzhang0421@163.com
create date: 2020 04 28
last modified date: 2020 04 28
					2020 08 01, the 1.0.1 version
features:
	+ compitable version, internal Windows functions support either Unicode or ANSI
*/

#ifndef AINRAY_WIN32API_H
#define AINRAY_WIN32API_H

#include <stdio.h>


#ifdef _WIN32_ //specialy win32api

#include<tchar.h>
#include <atlconv.h>
#include<windows.h>
#include<strsafe.h>
#include<Psapi.h>
#include<shellapi.h>
#pragma comment(lib, "User32.lib")
#pragma comment(lib,"Psapi.lib")
#pragma warning(disable:4996)

#else //unix

#include <unistd.h>

#endif //_WIN32_

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif // !FALSE

#ifdef _WIN32_
// for UNICODE or Chinese Wide Character set, 
// be sure that n is large twice as the number of character
#define MAX_PATH2 (MAX_PATH * 2)

#endif //_WIN32_
// ------------------------ c interface ---------------------------
int dir_create(char *path);
int dir_exist(const char *dirName_in);
int dir_list(char *dir, char ***subdirs);
int dir_remove(char *path, int confirm=FALSE);
int dir_rename(char *pTo, char *pFrom);

int file_exist(const char *fileName);

char *getcurrentpath(char *path, int n);
char* getuserpath(char *path, int n);

char*  readinifile(const char *section, const char *name, char *value, int len, const char *fname);
double readinifile(char *section, char *name, int len, char *fname); 
void writeinifile(const char *section,const char *name, const char *value,const char *fname);
void writeinifile(const char *section,const char *name, double value, int len, const char *fname);

int syscall(const char *exefullname, const char *argv);
int sysworkmemorymb(); //obtain system work memory, useful for debug in old vs version

#endif
