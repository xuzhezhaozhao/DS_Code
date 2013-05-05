/* 顺序串基本操作实现 */

#include <stdio.h>
#include <stdlib.h>

#include "my_headers.h"

/**
 * 生成一个其值等于chars的串T, chars是字符串常量
 */
Status StrAssign(SString &T, char *chars)
{
	int i = 0;
	while ('\0' != *(chars+i) && i < MAXSTRLEN) {
		T[i+1] = *(chars+i);
		++i;
	}
	T[0] = i;	//串长度赋给0号单元
	
	return 0;
}

/**
 * 由串S复制得串T
 */
Status StrCopy(SString &T, SString S)
{
	int i;
	for (i=0; i<=S[0]; i++) {
		T[i] = S[i];
	}
	return 0;
}

/**
 * 串S为空串，返回true，否则返回false
 */
bool StrEmpty(SString S)
{
	if (0 == S[0])
		return true;
	return false;
}

/**
 * 若S>T, 返回>0, S=T, =0, S<T, <0
 */
Status StrCompare(SString S, SString T)
{
	int i = 1, j = 1;
	while (i<=S[0] && j<=T[0]) {
		if (S[i] > T[i])
			return 1;
		else if (S[i] < T[i])
			return -1;
		else {
			i++;
			j++;
		}
	}
	if (S[0] == T[0])	//串长相等时
		return 0;
	else if (S[0] < T[0])
		return -1;
	else
		return 1;
}

/**
 * 返回串长度
 */
int StrLength(SString S)
{
	return S[0];
}

/**
 * 将S清为空串
 */
void ClearString(SString &S)
{
	S[0] = 0;
}

/**
 * 用T返回S1和S2连接起来的串
 */
void Concat(SString &T, SString S1, SString S2)
{
	int t = 1, s = 1;
	while (t <= MAXSTRLEN && s <= S1[0]+S2[0]) {
		if (s <= S1[0])
			T[t++] = S1[s++];
		else {
			T[t++] = S2[s-S1[0]];
			++s;
		}
	}
	T[0] = t-1;
}

/**
 * 打印串
 */
void displayStr(SString T)
{
	int i = 1;
	while (i <= T[0])
		printf("%c", T[i++]);
}

/**
 * 用Sub返回串S的第pos个字符起长度为len的子串，参数不合法返回ERROR, 否则返回OK
 */
Status SubString(SString &Sub, SString S, int pos, int len)
{
	int i, j;
	i = pos;
	j = 1;
	if (pos < 1 || pos > S[0] 
		|| len < 0 || len > S[0]-pos +1)	// 参数不合法
			return ERROR;
	 while (j <= len) {
		Sub[j] = S[i];
		++i;
		++j;
	 }
	 Sub[0] = len;
	 return OK;
}

/**
 * 查找主串S中第pos-1个字符后的子串T位置, 不存在返回0, T为非空串
 */
int Index(SString S, SString T, int pos)
{
	int i, j;
	i = pos;
	j = 1;
	if (pos < 1 || pos > S[0] || 0 == T[0])	//参数不合法
		return ERROR;
	while (i <= S[0]) {
		if (S[i] == T[j]) {
			i++;
			j++;
		} else {
			i = i-j+2;
			j = 1;
		}

		if (j == T[0]+1)	//存在匹配的子串
			return (i-j+1);
	}
	return 0;
	
}

/**
 * T是非空串，用V替换主串中所有与T相等的不重叠的子串
 */
Status Replace(SString &S, SString T, SString V)
{
	int pos;
	pos = 1;
	pos = Index(S, T, pos);
	while (0 != pos && ERROR != pos) {	//找到了子串
		StrDelete(S, pos, T[0]);	//先删除子串
		StrInsert(S, pos, V);		//再插入要替换的串
		pos = Index(S, T, pos+V[0]);
	}
	return OK;
}

/**
 * 在串S的第pos个字符之前插入串T, 遵循截断原则
 */
Status StrInsert(SString &S, int pos, SString T)
{
	int tlen, slen;
	int i, j, k;
	k = 0;
	
	if (pos < 1 || pos > S[0]+1)	//参数不合法
		return ERROR;
	tlen = T[0];
	slen = S[0];
	i = pos;
	j = 1;
	if (pos == S[0]+1) {	//插在最后面的情况
		while (S[0]+j <= MAXSTRLEN && j <= T[0]) {
			S[S[0]+j] = T[j];
			j++;
		}
		if (j <= T[0])	//空间不够，截断了
			S[0] = MAXSTRLEN;
		else
			S[0] = S[0] + T[0];
	} else {		//插在中间的情况
		for (i=S[0]; i>=pos; i--) {
			if (i+tlen <= MAXSTRLEN)
				S[i+tlen] = S[i];
			else
				k = i;	// 溢出的位置
		}
		i = pos;
		j = 1;
		while (i <= MAXSTRLEN && j <= tlen) {
			S[i] = T[j];
			i++;
			j++;
		}
		if (j <= T[0])
			S[0] = MAXSTRLEN;
		else {
			if (k != 0)	//插入后溢出了
				S[0] = MAXSTRLEN;
			else 
				S[0] = S[0] + T[0];
		}
	}
	return OK;
}

/**
 * 从串S中删除第pos个字符起长度为len的子串
 */
Status StrDelete(SString &S, int pos, int len)
{
	int i, j;
	if (pos < 1 || pos > S[0]-len+1)
		return ERROR;
	if (S[0] == pos+len-1)
		S[0] = S[0]-len;
	else {
		i = pos+len;
		while (i <= S[0]) {	//删除子串
			S[i-len] = S[i];
			i++;
		}
		S[0] = S[0]-len;
	}
	return OK;
}
