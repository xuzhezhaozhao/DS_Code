/* 八皇后问题递归求解 */

#include <stdio.h>
#include <stdlib.h>

#include "my_headers.h"

int chess[8][8] = {0};
int count = 0;		//解的个数
/**
 * 算法6.16，八皇后问题求解
 * 进入本函数前，在N*N的棋盘上前i-1行已经放置了互不攻击的i-1个棋子
 * 现从第i行起继续为后面的棋子选择合适的位置
 * 当i>n，输出当前布局
 */
void trial(int i, int n)
{
	int j;
	if (i > n)
		display_chess(n);
	else {
		for (j=1; j<=n; j++) {
			put(i, j);	//在i行j列摆放一颗棋子
			if (isReasonable(n, i, j))
				trial(i+1, n);
			remove(i, j);	//移除i行j列的棋子
		}
	}
}

/**
 * 打印当前棋盘
 */
void display_chess(int n)
{
	int i, j;
	count++;	//解的个数加1
	printf("%d.\n", count);
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++)
			printf("%d ", chess[i][j]);
		printf("\n");
	}
	printf("-----------------------------------\n");
}


/**
 * 在第i行第j列放置棋子
 */
void put(int i, int j)
{
	chess[i-1][j-1] = 1;
}

/**
 * 移除第i行第j列棋子
 */
void remove(int i, int j)
{
	chess[i-1][j-1] = 0;
}

/**
 * 在第row行第col放置皇后是否合法，合法返回true
 */
bool isReasonable(int n, int row, int col)
{
	int i, j, count1, count2, count3;
	count1 = count2 = count3 = 0;
	for (i=0; i<n; i++) {
		count3 = 0;
		for (j=0; j<n; j++) {
			if (i-j == row-col && 1 == chess[i][j])
				count1++;
			if (i+j == row+col-2 && 1 == chess[i][j])
				count2++;
			if (i+1 == col && 1 == chess[j][i])
				count3++;
		}
		if (count3 > 1)
			return false;
	}
	if (count1 > 1 || count2 > 1)
		return false;
	return true;
}