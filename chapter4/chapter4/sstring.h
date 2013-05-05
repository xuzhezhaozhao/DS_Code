/* 定长顺序串存储定义 */

#ifndef _SSTRING_H_
#define _SSTRING_H_

#define MAXSTRLEN 255
typedef unsigned char SString[MAXSTRLEN + 1];	//0号单元存储串长度

Status StrAssign(SString &T, char *chars);
Status StrCopy(SString &T, SString S);
bool StrEmpty(SString S);
Status StrCompare(SString S, SString T);
int StrLength(SString S);
void ClearString(SString &S);
void Concat(SString &T, SString S1, SString S2);
void displayStr(SString T);
Status SubString(SString &Sub, SString S, int pos, int len);
int Index(SString S, SString T, int pos);
Status Replace(SString &S, SString T, SString V);
Status StrInsert(SString &S, int pos, SString T);
Status StrDelete(SString &S, int pos, int len);

#endif