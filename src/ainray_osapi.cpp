#include "ainray_osapi.h"

#ifdef _WIN32_

// ---- C String convector from or to WIN32 String ------
LPTSTR str_c2win32(LPTSTR dst, int dsize, const char * src);
char * str_win322c(char * dst, int dsize, LPCTSTR src);

// one more for null-terminaled
#define WIN32STR_ALLOC(ptr, n) (ptr = (LPTSTR)(calloc(n+1, sizeof(TCHAR)))) 
#define STR_C2WIN32(tpath, path) {int n = (int)strlen(path);WIN32STR_ALLOC(tpath, n);str_c2win32(tpath, n, path);}

#endif

int dir_create(const char *path)
{
	int ret = 0;
#ifdef _WIN32_
	LPTSTR tpath;
	STR_C2WIN32(tpath, path);
	if(!CreateDirectory(tpath, NULL))
		ret = -1;

	free(tpath);
#else

#endif
	return ret;
}
int dir_copy(char *pTo, char *pFrom)
{
	// path shoud be double-null terminated
/*	SHFILEOPSTRUCT FileOp{ 0 };
	FileOp.fFlags = FOF_SILENT | FOF_NOERRORUI | FOF_NOCONFIRMMKDIR | FOF_NOCONFIRMATION;
	FileOp.pFrom = pFrom;
	FileOp.pTo = pTo;
	FileOp.wFunc = FO_COPY;
	int ret = SHFileOperation(&FileOp);
	if (FileOp.fAnyOperationsAborted == TRUE)
		ret = -1;
	return ret;*/
	return 0;
}
int dir_list(char *dir, char ***subdirs)
{
	int cnt = 0;
#ifdef _WIN32_
	WIN32_FIND_DATA ffd;
	TCHAR szDir[MAX_PATH];
	HANDLE hFind = INVALID_HANDLE_VALUE;

	str_c2win32(szDir, MAX_PATH, dir);
	StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

	// Find the first file in the directory.
	hFind = FindFirstFile(szDir, &ffd);
	if (INVALID_HANDLE_VALUE == hFind)
		return -1;
	// List all the files in the directory with some info about them.
	// first count it
	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			++cnt;
	} while (FindNextFile(hFind, &ffd) != 0);
	FindClose(hFind);

	*subdirs = (char **)calloc(cnt, sizeof(char *));
	for (int i = 0; i < cnt; ++i)
	{
		*(*subdirs + i) = (char *)calloc(MAX_PATH2, sizeof(char));
	}

	hFind = FindFirstFile(szDir, &ffd);
	for (int i = 0; FindNextFile(hFind, &ffd) != NULL;)
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			str_win322c(*(*subdirs + i), MAX_PATH2, ffd.cFileName);
			++i;
		}
	}
	FindClose(hFind);
#else

#endif
	return cnt;
}
int dir_remove(const char * path, int confirm)
{
	// path shoud be double-null terminated
	int ret = 0;
#ifdef _WIN32_
	SHFILEOPSTRUCT FileOp;
	memset(&FileOp, 1, sizeof(FileOp));
	if (confirm == TRUE)
		FileOp.fFlags = FOF_ALLOWUNDO; //允许放回回收站
	else
		FileOp.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION |FOF_NOERRORUI|FOF_NO_UI;
	
	LPTSTR tpath;
	STR_C2WIN32(tpath, path);

	FileOp.pFrom = tpath;
	FileOp.pTo = NULL; //一定要是NULL
	FileOp.wFunc = FO_DELETE; //删除操作
	ret = SHFileOperation(&FileOp);
	if (FileOp.fAnyOperationsAborted == TRUE)
		ret = -1;

	free(tpath);
#endif
	return ret;
}
int dir_rename(const char *pTo, const char *pFrom)
{
	int ret = 0;
#ifdef _WIN32_
	// pTo and pFrom shoud be double-null terminated
	/*SHFILEOPSTRUCT FileOp = { 0 };
	FileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR | FOF_NOERRORUI | FOF_SILENT; //不出现确认对话框
	FileOp.pFrom = pFrom;
	FileOp.pTo = pTo;
	FileOp.wFunc = FO_MOVE;
	int ret = SHFileOperation(&FileOp);
	if (FileOp.fAnyOperationsAborted == TRUE)
		ret = -1;
	return ret;*/
	LPTSTR tpFrom, tpTo;
	STR_C2WIN32(tpFrom,pFrom);
	STR_C2WIN32(tpTo, pTo);
	ret = MoveFile(tpFrom, tpTo);

	free(tpFrom);
	free(tpTo);
#else

#endif
	return ret;
}

int dir_exist(const char *dirName_in)
{
	if (dirName_in[0] == '\0')
            return FALSE;
	
	int ret = FALSE;

#ifdef _WIN32_
	LPTSTR tdirName_in;
	STR_C2WIN32(tdirName_in, dirName_in);

	DWORD ftyp = GetFileAttributes(tdirName_in);
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		ret = FALSE;  //something is wrong with your path!
	else if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		ret =TRUE;   // this is a directory!
	else
		ret = FALSE;

	free(tdirName_in);
#else

#endif

	return ret ;    // this is not a directory!
}

int file_exist(const char *fname)
{

	int ret = FALSE;
#ifdef _WIN32_
	LPTSTR fileName;
	STR_C2WIN32(fileName, fname);
#ifdef _TEST_
	printf("in function file_exist: %s\n", fname);
#endif	
	DWORD       fileAttr;
	fileAttr = GetFileAttributes(fileName);
	if ( (fileAttr ^ FILE_ATTRIBUTE_DIRECTORY) && (fileAttr != INVALID_FILE_ATTRIBUTES))
		ret = TRUE;
	free(fileName);

#else

        ret =  !access(fname, F_OK);
#endif
	return ret;
}
char *getuserpath(char *path, int n)
{
#ifdef _WIN32_
	LPCTSTR homeProfile = _T("USERPROFILE");
	TCHAR tpath[MAX_PATH];

	int ps = GetEnvironmentVariable(homeProfile, tpath, n);
	if (ps == 0 || ps > n)
	{
		return NULL;
	}
	else
	{
		path[0] = '\0';
		str_win322c(path, n, tpath);
		return path;
	}
#else

		return path;
#endif
}
char* getcurrentpath(char *path, int n)
{
#ifdef _WIN32_
	TCHAR tpath[MAX_PATH];
	int dwRet = GetModuleFileName(NULL, tpath, n);
	if (dwRet > n)
	{
		return NULL;
	}
	else
	{
		path[0] = '\0';
		str_win322c(path, n, tpath);
		return path;
	}
#else

		return path;
#endif
}

char*  readinifile(const char *section, const char *name, char *value, int len, const char *fname)
{
#ifdef _WIN32_
	LPTSTR tsection, tname, tfname;
	
	STR_C2WIN32(tsection, section);
	STR_C2WIN32(tname, name);
	STR_C2WIN32(tfname, fname);

	int len2 = len;
#ifdef UNICODE
        len2 = len/2;
#endif
	LPTSTR tvalue = (LPTSTR) (calloc(len2, sizeof(TCHAR)));
	GetPrivateProfileString(tsection, tname, _T(""), tvalue, len2, tfname);
	
	str_win322c(value, len, tvalue);
	free(tsection);
	free(tname);
	free(tfname);
#else

#endif
	return value; 
}

double readinifile(char *section, char *name, int len, char *fname)
{
	double vvalue=0.0;
#ifdef _WIN32_
	LPTSTR tsection, tname, tfname;
	
	STR_C2WIN32(tsection, section);
	STR_C2WIN32(tname, name);
	STR_C2WIN32(tfname, fname);

	int len2 = len;
#ifdef UNICODE
	len2 = len/2;
#endif

	LPTSTR tvalue = (LPTSTR) (calloc(len2, sizeof(TCHAR)));
	GetPrivateProfileString(tsection, tname, _T(""), tvalue, len2, tfname);

	char *value = (char *)calloc(len, sizeof(char));
	str_win322c(value, len, tvalue);

	vvalue=strtod(value, NULL);
	
	free(tsection);
	free(tname);
	free(tfname);
	free(tvalue);
	free(value);
#else
#endif
	return vvalue;
}


void writeinifile(const char *section,const char *name, const char *value,const char *fname)
{
#ifdef _WIN32_
	LPTSTR tsection, tname, tfname, tvalue;
	
	STR_C2WIN32(tsection, section);
	STR_C2WIN32(tname, name);
	STR_C2WIN32(tfname, fname);
	STR_C2WIN32(tvalue, value);

	WritePrivateProfileString(tsection, tname, tvalue, tfname);

	free(tsection);
	free(tname);
	free(tfname);
	free(tvalue);
#else

#endif
}
void writeinifile(const char *section,const char *name, double value, int len, const char *fname)
{
#ifdef _WIN32_
	LPTSTR tsection, tname, tfname, tvalue;
	
	STR_C2WIN32(tsection, section);
	STR_C2WIN32(tname, name);
	STR_C2WIN32(tfname, fname);

	char *buf = (char *)calloc(len, sizeof(char)); 
	_snprintf(buf, len, "%lf", value);

	STR_C2WIN32(tvalue, buf);

	WritePrivateProfileString(tsection, tname, tvalue, tfname);

	free(buf);
	free(tsection);
	free(tname);
	free(tfname);
	free(tvalue);
#else
#endif
}

#ifdef _WIN32_
LPTSTR str_c2win32(LPTSTR dst, int dsize, const char * src)
{
#ifdef UNICODE
	USES_CONVERSION;
	StringCchCopy(dst, dsize+1, A2W(src));
	return dst;
#else
	StringCchCopy(dst, dsize+1, src);
	return dst;
#endif

}
char * str_win322c(char * dst, int dsize, LPCTSTR src)
{
#ifdef UNICODE
	USES_CONVERSION;
	StringCchCopyA(dst, dsize+1, W2A(src));
	return dst;
#else
	StringCchCopy(dst, dsize+1, src);
	return dst;
#endif
}
#endif
int syscall(const char *exefullname, const char *argv)
{
#ifdef _WIN32_

	// WinExec("\"C:\\Program Files\\MyApp.exe\" -L -S", ...)
	char cmdline[RESTART_MAX_CMD_LINE];

	if(argv == NULL)
		_snprintf(cmdline,RESTART_MAX_CMD_LINE, "\"%s\"", exefullname);
	else
		_snprintf(cmdline,RESTART_MAX_CMD_LINE, "\"%s\" \"%s\"", exefullname, argv);

	LPTSTR tcmdline;
	STR_C2WIN32(tcmdline, cmdline);
	//return  WinExec(cmdline, SW_SHOW);

	STARTUPINFO stStartUpInfo = { sizeof(stStartUpInfo) };
	PROCESS_INFORMATION piProcessInfo;
	ZeroMemory(&stStartUpInfo, sizeof(STARTUPINFO));
	stStartUpInfo.cb = sizeof(STARTUPINFO);
	stStartUpInfo.dwFlags = STARTF_USESHOWWINDOW;
	stStartUpInfo.wShowWindow = SW_SHOW;//窗口显示为0不显示 
	CreateProcess(
		NULL,//应用程序名称 
		tcmdline, //命令行 
		NULL, //进程句柄不能被继承 
		NULL, //线程句柄不能被继承 
		FALSE,
		NULL,
		NULL,
		NULL,
		&stStartUpInfo,
		&piProcessInfo);
	int dwExitCode = WaitForSingleObject(piProcessInfo.hProcess, INFINITE); 
	TerminateProcess(piProcessInfo.hProcess, 0);
	CloseHandle(piProcessInfo.hProcess);
	CloseHandle(piProcessInfo.hThread);
#else

#endif
	return 0;
}

int sysworkmemorymb()
{
        int res = 0;
#ifdef _WIN32_
	HANDLE handle = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
	res = (int)pmc.WorkingSetSize/1024/1024;
#endif
        return res;
}
