#include "ainray_error.h"

#define _ERROR_BUFLEN_ 2048

static char errorinfobuf[_ERROR_BUFLEN_];
static int __error_no__ = 0;
static int __error_offset__ = 0;
static int __error_len__ = _ERROR_BUFLEN_;

void seterrorinfo(char *s)
{
	int n = 0;
	if (__error_offset__ > 0) //not empty, padding linefeed
	{
		if (__error_len__ < 1)
			return;
		n = snprintf(errorinfobuf + __error_offset__, __error_len__, "\n");
		__error_len__ -= n;
		__error_offset__ += n;
	}
	if (__error_len__ < 1)
		return;

	n = snprintf(errorinfobuf + __error_offset__, __error_len__, "%s", s);
	__error_len__ -= n;
	__error_offset__ += n;
}
char *geterrorinfo()
{
	__error_len__ = _ERROR_BUFLEN_; //flush buffer
	__error_offset__ = 0;

	return errorinfobuf;
}
int	 getlasterrorno()
{
	return __error_no__;
}
void seterrorno(int errno)
{
	__error_no__ = errno;
}
