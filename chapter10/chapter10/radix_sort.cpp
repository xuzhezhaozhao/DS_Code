/* 基数排序 */

#include <stdio.h>

#include "my_headers.h"

/**
 * 算法10.15，分配算法，静态链表L的r域中记录已按(key[0]...key[i-1])有序，
 * 本算法按第i个关键字建立RADIX个子表，使同一子表中记录的key[i]相同，
 * f[0...RADIX-1]和e[0...RADIX-1]分别指向各子表中第一个记录和最后一个记录.
 */
void Distribute(SLCell r[], int i, ArrType &f, ArrType &e)
{
	int j, p;
	for (j = 0; j < RADIX; j++) {	//初始化f[]
		f[j] = 0;
	}
	for (p = r[0].next; p != 0; p = r[p].next) {
		j = ord(r[p].keys[i]);
		if (!f[i]) {
			f[j] = p;
		} else {
			r[e[j]].next = p;
		}
		e[j] = p;
	}
}

/**
 * 将关键字K映射到[0...RADIX-1]
 */
int ord(KeysType K)
{
	return K;
}

/**
 * 算法10.16，收集算法，
 */
void Collect(SLCell r[], int i, ArrType f, ArrType e)
{
	int j, t;
	for (j = 0; f[j] != 0; j = succ(f, j)) {
		;
	}
	r[0].next = f[j];
	t = e[j];
	while (j < RADIX) {
		for (j = succ(f, j); j < RADIX-1 && !f[i]; j = succ(f, j)) {
			;
		}
		if (f[j]) {
			r[t].next = f[j];
			t = e[j];
		}
	}
	r[t].next = 0;
}

/**
 * 求f[j]后的第一个非空子表
 */
int succ(ArrType f, int j)
{
	int i;
	for (i = j + 1; f[i] != 0; i++) {
		;
	}
	return i;
}

/**
 * 算法10.17，基数排序
 */
void RadixSort(SLList &L)
{
	int i;
	ArrType f, e;
	for (i = 0; i < L.recnum; ++i) {
		L.r[i].next = i + 1;
	}
	L.r[L.recnum].next = 0;
	for (i = 0; i < L.keynum; i++) {
		
		Distribute(L.r, i, f, e);
		Collect(L.r, i, f, e);
	}
}