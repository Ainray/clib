#include "ainray_c.h"

double average(double *x, int len, int offset, int n)
{
	if (len < 1 || n < 1)
		return 0.0;

	double sum = 0.0;
	for (int i = 0; i < n && offset + i < len; ++i)
	{
		sum += x[offset + i];
	}

	return sum / n;
}

// called by heapselect
void heapadjust(double array[], int index[],int parent, int length) {

	int temp = index[parent];				// temp save current parent
	int child = 2 * parent + 1;		// get left child
	while (child < length) {		// loop
		// select the larger child
		if (child + 1 < length && array[index[child]] > array[index[child+1]]) {
			child++;
		}

		// parent > childrens 
		if (array[temp] <= array[index[child]])
			break;

		// move the smaller child to parent
		//array[parent] = array[child];
		index[parent] = index[child];

		// further lookup the heap
		parent = child;
		child = 2 * child + 1;
	}
	//array[parent] = temp;	//move the first parent to current parent
	index[parent] = temp;
}

// head select m minimums from n coherences using heap with minimum on the top
// only last mall of index are valid: index(n-mall:n-1)
// this function is implemented which support multiple calling
// parameters:
//		index, size of n, store selected index, only last 'mall' of index are valid: index(n-mall:n-1)
int * heapselect(double list[], int index[], int m, int *mall, int n)
{
	int mm = *mall;
	if (m + mm > n)
		return NULL;

	if (mm < 1) // first calling
	{
		for (int i = 0; i < n; ++i)
			index[i] = i;

		// create the intial heap with minimum on the top
		for (int i = n / 2; i >= 0; i--) {
			heapadjust(list, index, i, n);
		}
	}

	//sort
	for (int i = n - 1 - mm; i >= n - m - mm ; i--) { 
		// swap the first and last element
		int temp = index[i];
		index[i] = index[0];
		index[0] = temp;

		// select maximum element
		heapadjust(list,index, 0, i);
	}
	*mall += m;
	return index;
}

char *mem_hexdump(char *buf, int len, int width, long addr, int size) 
{
#define CHECKLEN(offset, len1) \
	len1 -= n; \
	offset += n; \
	if(len1 < 1) \
		return buf;

	int offset = 0, n = 0, len1 = len;

	int cnt = 0;
	int res = size; 
	unsigned char *p = (unsigned char *)addr;
	while (res > 0) //more than one line
	{
		n = snprintf(buf + offset, len1, "%08x - ", addr + width * cnt); //address itself
		CHECKLEN(offset, len1);
		//len1 -= n;  //remaining space
		//offset += n;
		//if (len1 < 1) //no space
		//	return;

		for (int i = 0; i < width; ++i) //one line
		{
			n = snprintf(buf + offset, len1, "%02x%s", *p++, i == width - 1 ? "" : " ");
			CHECKLEN(offset, len1);
		}
		// ASCII format
		n = snprintf(buf + offset, len1, " ");
		CHECKLEN(offset, len1);

		p -= width;
		for (int i = 0; i < width; ++i) //char
		{
			if (isprint(*p))
			{
				n = snprintf(buf + offset, len1, "%c", *p++);
				CHECKLEN(offset, len1);
			}
			else
			{
				n = snprintf(buf + offset, len1, ".");
				CHECKLEN(offset, len1);
				++p;
			}
		}

		n = snprintf(buf + offset, len1, "\n"); //line break
		CHECKLEN(offset, len1);

		res -= width;
		++cnt;
	}
	if (res > 0) //remainder
	{
		n = snprintf(buf + offset, len1, "%08x - ", addr + width * cnt); //address itself
		CHECKLEN(offset, len1);

		for (int i = 0; i < res; ++i) //one line
		{
			n = snprintf(buf + offset, len1, "%02x%s", *p++, i == width - 1 ? "" : " ");
			CHECKLEN(offset, len1);
		}
		for (int i = res; i < width; ++i)
		{
			n = snprintf(buf + offset, len1, "  %s", i == width - 1 ? "" : " ");
			CHECKLEN(offset, len1);
		}
		// ASCII format
		n = snprintf(buf + offset, len1, " ");
		CHECKLEN(offset, len1);

		p -= res;
		for (int i = 0; i < width; ++i) //char
		{
			if (isprint(*p))
			{
				n = snprintf(buf + offset, len1, "%c", *p++);
				CHECKLEN(offset, len1);
			}
			else
			{
				n = snprintf(buf + offset, len1, ".");
				CHECKLEN(offset, len1);
				++p;
			}
		}

		n = snprintf(buf + offset, len1, "\n"); //line break
		CHECKLEN(offset, len1);
	}
	return buf;
#undef CHECKLEN
}

char *path_cat(int mode, char *fullpath, int n, ...)
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
		PATH_UDC(spath);
		if (*(spath + len - 1) == PATH_HYPHEN)
			*(spath + len - 1) = '\0';

		if (i == 0) {//first parts, need no prefixed "\" or "/"
			strcpy(fullpath, spath);
		}
		else {
			strcat(fullpath, PATH_SHYPHEN);
			strcat(fullpath, spath);
		}
	}
	if (mode == 0) //for path, add tailing "\" or "/" for path
		strcat(fullpath, PATH_SHYPHEN);
	va_end(ap);

	return fullpath;
}

char *path_catwithdzt(char *dst, int len, int n, ...)
{
#define CHECKLEN(offset, len1, n) \
	len1 -= (n+1); \
	offset += (n+1); \
	if(len1 < 1) \
		return NULL; 

	// check input arguments
	if (dst == NULL || n < 1)
		return NULL;

	// deal with input argument list
	char *spath;
	va_list ap;
	va_start(ap, n);
	int offset = 0;
	int len1 = len;
	int slen = 0;
	for (int i = 0; i < n; ++i) {
		spath = va_arg(ap, char *);

		if (i == 0) {//copy first one
			slen = snprintf(dst, len1, "%s", spath);
			CHECKLEN(offset, len1, slen);
		}
		else { //concatenate the tailing ones
			slen = snprintf(dst + offset, len1, "%s", spath);
			CHECKLEN(offset, len1, slen);
		}
	}
	dst[offset] = '\0'; //double null terminator
	va_end(ap);
	return dst;
#undef CHECKLEN
}

char *path_compact(char *path)
{
	//temporary implemation, no efficiency
	PATH_UDC(path);
	int n = (int)strlen(path);
	int state = 0; //out in default
	char *start = NULL, *ps = NULL;
	int i = 0;
	for (i = 0, ps = path; *ps != '\0'; ++ps, ++i)
	{
		if (*ps == PATH_HYPHEN)
		{
			if (state == 0)//step in
			{
				start = ps;
				state = 1;
			}
		}
		else if (*ps != '\0')
		{
			if (state == 1) //step out
			{
				//move the tailing block into "start+1"
				++start;
				if (start != ps)
				{
					memmove(start, ps, sizeof(char)*(n - i + 1));//include null terminator
					ps = start; //update ps into correct position
				}
				state = 0;
			}
		}
	}
	return path;
}

char *path_d2u(char *path)
{
	char *ps = path;
	while (*ps != '\0')
	{
		if (*ps == PATH_HYPHEN_DOS)
			*ps = PATH_HYPHEN_UNIX;
		++ps;
	}
	return path;
}

char *path_getdirectory(char *dir, int n, char *path)
{
	if (dir != path)
		strcopy(dir, n, path, n);

	PATH_UDC(dir);
	char *last = NULL;
	last = strrchr(path, PATH_HYPHEN);
	if (last != NULL)
		*last = '\0';
	return dir;
}

char *path_getfilename(char *fname, int n, char *path)
{
	if (fname != path) //out of place
	{
		strcopy(fname, n, path, n);
	}
	PATH_UDC(fname);
	char *last = NULL;
	last = strrchr(fname, PATH_HYPHEN);
	if (last != NULL)
	{
		int len = (int)strlen(last);
		memmove(fname, last + 1, len);
		return last + 1;
	}
	return NULL;
}

char *path_getfilenamewithoutext(char *purefname, int n, char *path)
{
	char filename[FILENAME_MAX];
	if (path_getfilename(filename, FILENAME_MAX, path) == NULL)
		return NULL;

	char *last = NULL;
	if ((last = strrchr(filename, '.')) != NULL)
	{
		if (*(last + 1) == '\0') //no ext
			return NULL;
		strcopy(purefname, n, filename, n);
		*(purefname + (last - filename)) = '\0';
	}
	return purefname;
}

char *path_u2d(char *path)
{
	char *ps = path;
	while (*ps != '\0')
	{
		if (*ps == PATH_HYPHEN_UNIX)
			*ps = PATH_HYPHEN_DOS;
		++ps;
	}
	return path;
}

// assume s only has digits
int stra2i(char *s, int len)
{
	int sum = 0;
	for (int i = 0; i < len; ++i)
	{
		sum = sum * 10 + s[i] - '0';
	}
	return sum;
}
char * strcopy(char *dst, int len, char *src, int n)
{
	if (n < 0)
		return NULL;
	if (n > len - 1)
		n = len - 1; //truncate

	strncpy(dst, src, n);
	dst[n] = '\0';
	return dst;
}
