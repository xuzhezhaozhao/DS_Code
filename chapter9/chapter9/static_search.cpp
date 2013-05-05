/* 静态表查找的相关算法实现 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "my_headers.h"

/**
 * 构造一个含n个数据元素的静态查找表ST，表中数据从指定文件filename中读取
 * 构造成功返回OK，打开文件失败错误返回FILE_NOT_EXIT，其他错误返回ERROR
 */
Status CreateTable(SSTable &ST, int n, char *filename)
{
	int i;
	FILE *pFile;
	ST.length = n;
	ST.elem = (ElemType *)malloc((ST.length+1) * sizeof(ElemType));
	if (NULL == ST.elem) {		//分配内存空间失败
		return ERROR;
	}
	pFile = fopen(filename, "r");
	if (pFile == NULL) {	//打开文件失败
		printf("打开文件%s失败！！！\n", filename);
		return FILE_NOT_EXIT;
	} else {		//成功打开文件
		for (i = 1; i <= ST.length; i++) {
				if (EOF == fscanf(pFile, "%d %s %f", 
					&ST.elem[i].key, 
					&ST.elem[i].data, 
					&ST.elem[i].weigth)) {
					printf("读取记录出错！！！\n", 
						i, filename, ST.length);
					return ERROR;
				}
			
		}
		fclose(pFile);
		return OK;
	}
}

/**
 * 静态查找表ST存在，销毁表ST
 */
void Destroy(SSTable &ST)
{
	if (ST.elem != NULL) {
		free(ST.elem);
		ST.elem = NULL;
		ST.length = 0;
	}
}

/**
 * 算法9.1，在顺序表ST中关键字等于key的数据元素
 * 若找到，返回元素位置，否则返回0
 */
int Search_Seq(SSTable ST, KeyType key)
{
	int i;
	ST.elem[0].key = key;		//“哨兵”
	for (i = ST.length; !EQ(ST.elem[i].key, key); i--) {
		;
	}
	return i;
}

/**
 * 算法9.2，有序表的折半查找
 * 若找到，返回元素位置，否则返回0
 */
int Search_Bi(SSTable ST, KeyType key)
{
	int low, mid, high;
	int temp;
	low = 1;		//初始化初始状态
	high = ST.length;
	while (low <= high) {
		mid = (low + high) / 2;
		if (LT(key, ST.elem[mid].key)) {		//中间值大
			high = mid - 1;
			
		} else if (LT(ST.elem[mid].key, key)) {		//中间值小
			low = mid + 1;
		} else {		// ST.elem[0].key == mid, 找到
			return mid;
		}
	}
	/* 执行完while循环后low > high, 表示没有找到值 */
	return 0;
}

/**
 * 算法9.3，递归构造次优先查找树T,sw[]中保存有序表R[0...length]的累计权值表
 * ΔPi = |(SWh + SWl-1) - (SWi + SWi-1)|
 */
void SecondOptimal(BiTree &T, ElemType R[], float sw[], int low, int high)
{
	int i, j;
	i = low;
	float min = fabs(sw[high]-sw[low]);	//初始化，当i = low的时候
	float dw = sw[high] + sw[low - 1];
	for (j = low + 1; j <= high; j++) {		//选择最小的ΔPi值
		if (fabs(dw - sw[j] - sw[j - 1]) < min) {
			i = j;
			min = fabs(dw - sw[j] - sw[j - 1]);
		}
	}

	T = (BiTree)malloc(sizeof(BiTNode));
	T->data.key = R[i].key;
	if (i == low) {
		T->lchild = NULL;	//左子树为空
	} else {
		SecondOptimal(T->lchild, R, sw, low, i-1);	//构造左子树
		
	}

	if (i == high) {
		T->rchild = NULL;	//右子树为空
	} else {
		SecondOptimal(T->rchild, R, sw, i+1, high);	//构造右子树
	}
}

/**
 * 计算有序表R[0...length]的累计权值，结果保存在sw[]中
 */
void getTableSW(ElemType R[], float sw[], int length)
{
	int i;
	sw[0] = 0;
	for (i = 1; i <= length; i++) {
		sw[i] = sw[i - 1] + R[i].weigth;
	}
}

/**
 * 算法9.4， 由有序表ST构造一棵次优查找树T
 */
Status CreateSOSTree(SOSTree &T, SSTable ST)
{
	float *sw;
	sw = (float *)malloc((ST.length+1) * sizeof(float));
	if (NULL == sw) {
		return ERROR;
	}
	if (0 == ST.length) {
		T = NULL;
	} else{
		getTableSW(ST.elem, sw, ST.length);
		SecondOptimal(T, ST.elem, sw, 1, ST.length);
	}
	return OK;
}