// author: Ainray
// date: 20160118
// bug-report: wwzhang0421@163.compare
// introduction:  general io functions

#ifndef CIO_H
#define CIO_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
#ifdef __cplusplus
extern "C" {
#endif
// function: firstupper(char *s)
// introduction: convert characters into the lower-case except the first if necessary
// date: 20160122
// note: this function does not check whether the string's character is an alphabet;
//     : this function runns in the in-place way, so the original string is changed.
void firstupper(char *s);

// function: getline 
// introduction: read a line with a limit of naximum number of characters per line
//               return the number of characters.
// note: this function does check the validity of file pointer;
//     : this function does alloc memory for the line buffer, i.e., s;
//     : this function does support at most 1000 characters per line;
int getline(FILE *pfile,char *s, int lim);

// function: isalphas
// introduction: check whether all characters of a string is alphabe
//             : return false or true.
// date: 20160122
int isalphas(char *s);


// function: lower 
// introduction: convert characters into the lower-case if necessary
// date: 20160122
// note: this function does not check whether the string's character is an alphabet;
//     : this function runns in the in-place way, so the original string is changed.
void lower(char *s);

// function: putcs
// introduction: write a string into a file
// date: 20160122
// note: this function does not check the validity of file pointer;
//	   : this function does not close the file after writing.
int putcs(FILE *pfile, char *s);

// function: putline
// introduction: write a string as line into a file, if the last character is not newline,
//             : this function manually put a newline
// date: 20160122
// note: this function does not check the validity of file pointer;
//	   : this function does not close the file after writing.
int putline(FILE *pfile, char *s);

// function: strstrs
// introduction: find string "s1", within array of strings, "s1".
// date:20160127
// note: this function does not check the validity of pointers.
// 	   : this function return the index starting at zero, if "s2" within "s1"
//     : by "pos" parameter, which is the number of strings in "s1".
//     : this function also return the pointer of first occurance of "s2" within
//     : "s1[index]".
char * strstrs(char *s1[], char *s2,int num,int *pos,int caseswitch);

// function: str2word
// introduction: covert string into word-by-word string array,
//             : return the number of words.
// date: 20160122
// note: this function does not alloc memory for buffer containing words
//     : this function does not assume limit of the number of words.
int str2word(char *s, char **ws);

// function: upper 
// introduction: convert characters into the upper-case if necessary
// date: 20160122
// note: this function does not check whether the string's character is an alphabet;
//     : this function runns in the in-place way, so the original string is changed.
void upper(char *s);

#ifdef __cplusplus
}
#endif

#endif