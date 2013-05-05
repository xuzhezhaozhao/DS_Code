#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "my_headers.h"

/**
 * 从文件filename中读入数据创建顺序表L，0号单元不用
 */
Status CreateSqList(SqList &L, char *filename)
{
	InitList_Sq(L);

	FILE *pf;
	ElemType e;

	pf = fopen(filename, "r");
	if (NULL == pf) {
		printf("打开文件%s失败！\n", filename);
		return ERROR;
	}
	while (fscanf(pf, "%d", &e) != EOF) {
		ListInsert_Sq(L, 2, e);
	}
	fclose(pf);
	return OK;
}

/**
 * 算法10.1，对顺序表作插入排序
 */
void InsertSort(SqList &L)
{
	int i, j;
	for (i = 2; i <= L.length; i++) {
		if (L.elem[i] < L.elem[i-1]) {	//寻找合适的插入位置
			L.elem[0] = L.elem[i];
			L.elem[i] = L.elem[i-1];
			for (j = i-2; 
				L.elem[0] < L.elem[j]; j--) {
					L.elem[j+1] = L.elem[j];//记录后移
			}
			L.elem[j+1] = L.elem[0];	//插入到正确位置
		}
	}
}

/**
 * 算法10.2，折半插入排序
 */
void BInsertSort(SqList &L)
{
	int i, j, low, high, mid;
	for (i = 2; i <= L.length; i++) {
		L.elem[0] = L.elem[i];
		high = i - 1;
		low = 1;
		while (high >= low) {	//折半查询插入位置，应为low位置
			mid = (high + low) / 2;
			if (L.elem[0] < L.elem[mid]) {
				high = mid - 1;
			} else {
				low = mid + 1;
			}
		}
		for (j = i - 1; j >= low; j--) {	//记录后移
			L.elem[j+1] = L.elem[j];
		}
		L.elem[low] = L.elem[0];
	}
}

/**
 * 2－路插入排序算法
 */
void TwoInsertSort(SqList &L)
{
	ElemType *d;
	int first, final, i, j;
	d = (ElemType *)malloc((L.length+1) * sizeof(ElemType));
	first = 0;
	final = 0;
	if (L.length > 0) {
		d[1] = L.elem[1];	//L中的第一个元素作d的中间位置
		first = 0;
		final = 1;
	}
	
	for (i = 2; i <= L.length; i++) {
		if (L.elem[i] > d[1]) {	//插入到后部分
			for (j = final; L.elem[i] < d[j]; j--) {	
				d[j+1] = d[j];	//记录后移
			}
			++final;
			d[j+1] = L.elem[i];	//插入
		} else {	//插入到前部分
			if (0 == first) {
				first = L.length;
				d[L.length] = L.elem[i];
			} else {
				for (j = first; L.elem[i] > d[j]; j++) {
					d[j - 1] = d[j];	//记录后移
				}
				--first;
				d[j-1] =L.elem[i]; 
			}
		}
	}

	if (0 == first) {
		for (i = 1; i <= L.length; i++) {
			L.elem[i] = d[i];
		}
	} else {
		for (i = first, j = 1; i <= L.length; i++, j++) {
			L.elem[j] = d[i];
		}
		for (i = 1; i <= final; i++, j++) {
			L.elem[j] = d[i];
		}
	}
}

/**
 * 静态表插入排序
 */
void TableInsertSort(SLinkList &S)
{
	int i, j, p;
	S.r[0].key = INT_MAX;
	
	if (S.length > 0) {
		S.r[1].next = 0;
		S.r[0].next = 1;
	}
	
	for (i = 2; i <= S.length; i++) {
		p = 0;
		for (j = S.r[0].next; S.r[i].key > S.r[j].key && j > 0; 
			p = j, j = S.r[j].next) {	//寻找插入位置
			;
		}
		S.r[i].next = j;
		S.r[p].next = i;
	}
}

/**
 * 创建静态链表，从文件filename中读取数据，读取失败返回ERROR
 */
Status CreateSLinkList(SLinkList &S, char *filename)
{
	FILE *pf;
	int key, i;
	i = 1;
	S.length = 0;
	pf = fopen(filename, "r");
	if (NULL == pf) {
		printf("打开文件%s失败！\n", filename);
		return ERROR;
	}
	while (EOF != fscanf(pf, "%d", &key)) {
		S.r[i].key = key;
		S.length++;
		++i;
	}
	fclose(pf);
	return OK;
}

/**
 * 算法10.3，根据静态链表SL中各结点的指针值调整记录位置，使得SL中记录按关键字非递减有序
 * 顺序排列
 */
void Arrang(SLinkList &SL)
{
	int p, q, i, temp;
	p = SL.r[0].next;	//指向链表中的第一个记录
	for (i = 1; i <= SL.length; i++) {
		if (p != i) {
			swap(SL.r[i].key, SL.r[p].key);
			q = SL.r[p].next;
			SL.r[p].next = SL.r[i].next;
			SL.r[i].next  = p;
			p = q;
		}

		while (p <= i && p != 0) {
			p = SL.r[p].next;
		}
	}
}

/**
 * 交换两个数i, j
 */
void swap(int &i, int &j)
{
	int temp;
	temp = i;
	i = j;
	j = temp;
}

/**
 * 算法10.4
 */
void ShellInsert(SqList &L, int dk)
{
	int i, j;
	for (i = dk + 1; i <= L.length; i++) {
		if (L.elem[i] < L.elem[i - dk]) {
			L.elem[0] = L.elem[i];
			for (j = i - dk; j > 0 && L.elem[0] < L.elem[j]; 
				j = j - dk) {
				L.elem[j + dk] = L.elem[j];
			}
			L.elem[j + dk] = L.elem[0];
		}
	}
}

/**
 * 算法10.5，希尔排序，按增量序列dlta[0...t-1]对顺序表L作希尔排序，
 * 且dlta[t-1]必须为1
 */
void ShellSort(SqList &L, int dlta[], int t)
{
	int k;
	for (k = 0; k < t; k++) {
		ShellInsert(L, dlta[k]);
	}
}