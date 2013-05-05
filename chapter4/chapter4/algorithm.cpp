#include <stdio.h>
#include <stdlib.h>

#include "my_headers.h"

/**
 * 算法4.1 到 4.5 为基本操作实现
 */

/**
 * 算法4.6，KMP算法
 */
int Index_KMP(SString S, SString T, int pos)
{
	int i = pos;
	int j = 1;
	int *next;
	next = (int *) malloc (T[0]*sizeof(int));
	if (!next)
		return ERROR;
	get_next(T, next);
	while (i <= S[0] && j <= T[0]) {
		if (0 == j || S[i] == T[j]) {
			++i;
			++j;
		} else
			j = next[j];
	}
	if (j > T[0])
		return i-T[0];	//匹配成功
	else
		return 0;
}

/**
 * 算法4.7，求模式串T的next函数值并存入数组next中
 */
void get_next(SString T, int next[])
{
	int i = 1;	// 将T看作主串时不匹配的字符位置
	int j = 0;	// 将T看作模式串时不匹配的字符位置
	next[0] = T[0];
	next[1] = 0;
	while (i < T[0]) {
		if (j == 0 || T[i] == T[j]) {	// j == 0时，next[i] = 1;
			++i;
			++j;
			next[i] = j;	// 此时是T[i-1] == T[j-1]
		}
		else
			j = next[j];	//不匹配时将模式串移到next[j]位置重新开始匹配
	}
}

/** 
 * 算法 4.8
 */
void get_nextval(SString, int nextval[])
{
	int i = 1;	// 将T看作主串时不匹配的字符位置
	int j = 0;	// 将T看作模式串时不匹配的字符位置
	nextval[0] = T[0];
	nextval[1] = 0;
	while (i < T[0]) {
		if (j == 0 || T[i] == T[j]) {	// j == 0时，next[i] = 1;
			++i;
			++j;
			if (T[i] != T[j])
				nextval[i] = j;	// 此时是T[i-1] == T[j-1]
			else
				nextval[i] = nextval[j];
		}
		else
			j = nextval[j];	//不匹配时将模式串移到next[j]位置重新开始匹配
	}
}