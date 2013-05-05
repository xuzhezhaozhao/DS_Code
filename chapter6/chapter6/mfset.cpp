#include <stdio.h>
#include <stdlib.h>

#include "my_headers.h"

/**
 * 算法6.8，找集合S中i所在子集的根
 */
int find_mfset(MFSet S, int i)
{
	int j;
	if (i<1 || i>S.n)
		return ERROR;
	for (j=i; S.nodes[j].parent>0; j=S.nodes[j].parent)
		;
	return j;
}


/**
 * 算法6.9，S.nodes[i]和S.nodes[j]分别为S的互不相交的两个子集Si和Sj的根结点，
 * 求并集SiUSj
 */
Status merge_mfset(MFSet &S, int i, int j)
{
	if (i<1 || i>S.n || j<1 || j>S.n)
		return ERROR;
	S.nodes[i].parent = j;
	return OK;
}

/**
 * 算法6.10，改进的求并集的算法，根结点的parent域中存储子集中所含元素的负值
 */
Status mix_mfset(MFSet &S, int i, int j)
{
	if (i<1 || i>S.n || j<1 || j>S.n)
		return ERROR;
	if (S.nodes[i].parent > S.nodes[j].parent) {	// Si所含成员数比Sj中少
		S.nodes[j].parent += S.nodes[i].parent;
		S.nodes[i].parent = j;
	} else {
		S.nodes[i].parent += S.nodes[j].parent;
		S.nodes[j].parent = i;
	}
	return OK;
}

/**
 * 算法6.11，算法6.8的改进，增加压缩路径，
 * 确定i所在子集，并将从i至根路径上所有结点都变成根的孩子结点
 */
int fix_mfset(MFSet &S, int i)
{
	int j, k, t;

	if (i<1 || i>S.n)
		return ERROR;
	for (j=i; S.nodes[j].parent>0; j=S.nodes[j].parent) //循环结束后 j 就是根结点
		;
	for (k=i; k!=j; k=t) {
		t = S.nodes[k].parent;
		S.nodes[k].parent = j;
	}
	return j;	//返回i所在子集的根结点
}