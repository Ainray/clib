#include "cio.h" // the head file path
void firstupper(char *s)
{
	if(s[0]<='z' && s[0]>='a')
		s[0]+='A'-'a';
	int i=1;
	while(s[i])
	{
		if(s[i]<='Z' && s[i]>='A')
			s[i]+='a'-'A';
		++i;
	}
}

int getline(FILE *pfile,char *s, int lim)
{
	int c,i;
	for(i=0;i< lim-1 && ( c=getc(pfile) )!=EOF && c!='\n'; ++i)
		s[i]=c;
	if (c=='\n')
		s[i++]=c;
	s[i]='\0';
	return i;
}

int isalphas(char *s)
{
	int i=0;
	while(s[i])
	{
		if(!( (s[i]<='Z' && s[i]>='A') || (s[i]<='z' && s[i]>='a')))
			return FALSE;
	}
	return TRUE;
} 

int line2word(char *s, char *ws[])
{
	int state=0;  //indicate within a word or not
	char *p=s;
	int i,j;
	char buf[256]; // a word at most 256 characters
	i=j=0;
	while(*p && *p!=EOF  && *p!='\n')  // *P='\0' inicate end of string
	{
		if((*p<='Z' && *p>='A') ||( *p<='z' && *p>='a') )
		{
			if(!state) // step from outside some word to inside
			{
				state=1; // within of some word
				j=0; // the first character of some word
				buf[j++]=*p;
			}
		}
		else if(state) // step from within some word to outside
		{
			state=0;
			buf[j]='\0';
			ws[i]=(char *)malloc(sizeof(char)*(j+1));
			strcpy(ws[i++],buf);
		}
		++p;
	
	}
}

void lower(char *s)
{
	int i=0;
	while(s[i])
	{
		if(s[i]<='Z' && s[i]>='A')
			s[i]+='a'-'A';
		++i;
	}
}

int putcs(FILE *pfile, char *s)
{
	int state=0;
	char *p=s;
	while(*p && *p !=EOF)
	{
		putc(*p,pfile);
		++p;
	}
	if(*p==EOF)
	{
		putc(*p,pfile);
		state=-1;
	}
}
int putline(FILE *pfile,char *s)
{
	int state=0;
	char *p=s;
	while(*p && *p !=EOF)
	{
		putc(*p,pfile);
		++p;
	}
	if(*p==EOF)
	{
		putc(*p,pfile);
		state=-1;
	}
	else if(*(--p)!='\n')
		putc('\n',pfile);
	return state;	
}

void upper(char *s)
{
	int i=0;
	while(s[i])
	{
		if(s[i]<='z' && s[i]>='a')
			s[i]+='A'-'a';
		++i;
	}
}