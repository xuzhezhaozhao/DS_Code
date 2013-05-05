#include <stdio.h>

#include "my_headers.h"

/**
 * 算法10.9，对顺序表作简单选择排序
 */
void SelectSort(SqList &L)
{
	int i, j;
	for (i = 1; i < L.length; i++) {
		j = SelectMinKey(L, i);
		if (i != j) {
			swap(L.elem[i], L.elem[j]);
		}
	}
}

/**
 * 选择L.r[i...L.length]中key最小的记录，返回其位置
 */
int SelectMinKey(SqList L, int i)
{
	int pos, k, min;
	min = L.elem[i];
	pos = i;
	for (k = i + 1; k <= L.length; k++) {
		if (min > L.elem[k]) {
			min = L.elem[k];
			pos = k;
		}
	}
	return pos;
}

/**
 * 算法10.10，已知H.r[s...m]中记录的关键字除H.r[s].key之外均满足堆的定义，
 * 本函数调整H.r[s]的关键字，使H.r[s...m]成为一个大顶堆
 */
void HeapAdjust(HeapType &H, int s, int m)
{
	int rc, j;
	rc = H.elem[s];
	for (j = 2 * s; j <= m; j = j * 2) {
		if (j < m && H.elem[j] < H.elem[j + 1]) {
			++j;
		}
		if (rc >= H.elem[j]) {
			break;;
		}
		H.elem[s] = H.elem[j];
		s = j;
	}
	H.elem[s] = rc;
}

/**
 * 算法10.11
 */
void HeapSort(HeapType &H)
{
	int i;
	for (i = H.length / 2; i > 0; i--) {
		HeapAdjust(H, i, H.length);
	}
	for (i = H.length; i > 1; i--) {
		swap(H.elem[1], H.elem[i]);
		HeapAdjust(H, 1, i - 1);
	}
}