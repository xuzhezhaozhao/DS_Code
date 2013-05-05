#include <stdio.h>

#include "my_headers.h"

/**
 * 算法10.6（a），交换顺序表L中子表L.r[low...high]的记录，使枢轴记录到位，
 * 并返回其所在位置，此时在它之前(之后）的记录不大（小）于它。
 */
int Partition_a(SqList &L, int low, int high)
{
	int pivotkey;
	pivotkey = L.elem[low];		//第一个记录作枢轴记录
	while (low < high) {
		while (low < high && L.elem[high] >= pivotkey) {
			--high;
		}
		swap(L.elem[low], L.elem[high]);
		while (low < high && L.elem[low] <= pivotkey) {
			++low;
		}
		swap(L.elem[low], L.elem[high]);
	}
	return low;
}

/**
 * 算法10.7(b)，对算法10.7(a)的改进算法，减少了交换的步骤
 */
int Partition(SqList &L, int low, int high)
{
	int pivotkey;
	L.elem[0] = L.elem[low];
	pivotkey = L.elem[low];		//第一个记录作枢轴记录
	while (low < high) {
		while (low < high && L.elem[high] >= pivotkey) {
			--high;
		}
		L.elem[low] = L.elem[high];
		while (low < high && L.elem[low] <= pivotkey) {
			++low;
		}
		L.elem[high] = L.elem[low];
	}
	L.elem[low] = L.elem[0];
	return low;
}

/**
 * 算法10.7，递归法对顺序表L中的子序列L.r[low...high]作快速排序
 */
void QSort(SqList &L, int low, int high)
{
	int pivotloc;
	if (low < high) {
		pivotloc = Partition(L, low, high);
		QSort(L, low, pivotloc - 1);
		QSort(L, pivotloc + 1, high);
	}
}

/**
 * 算法10.8，快速排序
 */
void QuickSort(SqList &L)
{
	QSort(L, 1, L.length);
}