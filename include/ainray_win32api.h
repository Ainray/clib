#ifndef AINRAY_WIN32API_H
#define AINRAY_WIN32API_H

/* Win32 interface lib for C program in Windows

author: Ainray
email: wwzhang0421@163.com
create date: 2020 04 28
last modified date: 2020 04 28

features: 
	+ compitable version, internal Windows functions support either Unicode or ANSI 
*/

// ------------------------ c interface ---------------------------

int dirCreate(char *path);
int dirExists(const char *dirName_in);
int dirList(char *dir, char ***subdirs);
int dirRemove(char *path, int confirm=FALSE);
int dirRename(char *pTo, char *pFrom);

int fileExists(const char *fileName);

// for UNICODE or Chinese Wide Character set, 
// be sure that n is large twice as the number of character
#define MAX_PATH2 (MAX_PATH * 2)
char *getcurrentpath(char *path, int n);
char* getuserpath(char *path, int n);

char*  readinifile(const char *section, const char *name, char *value, int len, const char *fname);
double readinifile(char *section, char *name, int len, char *fname); 
void writeinifile(const char *section,const char *name, const char *value,const char *fname);
void writeinifile(const char *section,const char *name, double value, int len, const char *fname);

int syscall(const char *exefullname, const char *argv);
int sysworkmemorymb(); //obtain system work memory, useful for debug in old vs version

#endif
