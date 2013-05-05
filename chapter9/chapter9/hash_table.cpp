#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "my_headers.h"

int hashsize[] = {11, 111, 997};	//哈希表容量递增表，一个合适的素数序列

/**
 * 算法9.17，在开放定址哈希表H中查找关键字为K的元素，若查找成功，以p指示待查数据，并返回
 * SUCCESS，否则以p指示插入位置，并返回UNSUCCESS，c统计冲突次数，其初值为0。当查找时
 * 发现哈希表已满时则重新哈希表扩大容量。
 */
Status SearchHash(HashTable &H, KeyType K, int &p, int &c)
{
	c = 0;		//冲突次数初始化
	p = Hash(K, hashsize[H.sizeindex]);
	while (H.elem[p].key != NULLKEY		//该表中有记录
		&& !EQ(K, H.elem[p].key)) {	//而且关键字不等
			c++;			//冲突次数加1
			if (c == hashsize[H.sizeindex]) {	//哈希表已满，重建
				p = hashsize[H.sizeindex];	//插入位置
				RecreateHashTable(H);
				return UNSUCCESS;
			}
			collision(p, c, hashsize[H.sizeindex]);		
	}
	if EQ(K, H.elem[p].key) {	//查找成功
		return SUCCESS;
	} else {	//查找不成功，p返回的是插入位置
		return UNSUCCESS;
	}
}

/**
 * 哈希函数，直接定址法
 */
int Hash(KeyType K, int p)
{
	return (K%p);
}

/**
 * 产生冲突时，由开放定址法生成下个位置，c为增量，len为哈希表长，由p返回该位置
 */
Status collision(int &p, int c, int len)
{
	if (c == len) {
		return ERROR;
	} else {
		p = (p + c) % len;
		return OK;
	}
	
}

/**
 * 算法9.17，查找不成功时插入数据元素e到开放定址哈希表H中，并返回OK，若冲突次数过大，
 * 则重建哈希表并返回UNSUCCESS。
 */
Status InsertHash(HashTable &H, ElemType e)
{
	int p, c;
	c = 0;
	if (SearchHash(H, e.key, p, c) == SUCCESS) {
		return DUPLICATE;
	} else if (c < hashsize[H.sizeindex] / 2) {
		H.elem[p] = e;
		H.count++;
		return OK;
	} else {
		RecreateHashTable(H);
		return UNSUCCESS;
	}
}

/**
 * 重建哈希表，成功返回OK，失败返回ERROR
 */
Status RecreateHashTable(HashTable &H)
{
	int i;
	H.elem = (ElemType *)realloc(H.elem, 
			hashsize[H.sizeindex + 1] * sizeof(ElemType));
	if (NULL == H.elem) {
		return ERROR;
	} else {
		for (i = hashsize[H.sizeindex]; 
			i < hashsize[H.sizeindex + 1]; i++) {
			H.elem[i].key = NULLKEY;
		}
		H.sizeindex++;
		return OK;
	}
	
}

/**
 * 初始化哈希表，成功返回OK，失败返回ERROR
 */
Status InitHashTable(HashTable &H)
{
	H.sizeindex = 0;
	H.count = 0;
	H.elem = (ElemType *)malloc(hashsize[H.sizeindex] * sizeof(ElemType));
	if (NULL == H.elem) {
		return ERROR;
	}
	for (int i = 0; i < hashsize[H.sizeindex]; i++) {
		H.elem[i].key = NULLKEY;
	}
	return OK;
}

/**
 * 从文件filename中读入数据建立哈希表H，成功返回OK，失败返回ERROR
 */
Status CreateHashTable(HashTable &H, char *filename)
{
	ElemType e;
	FILE *pf;
	InitHashTable(H);
	pf = fopen(filename, "r");
	if (NULL == pf) {
		printf("打开文件%s失败！\n", filename);
		return ERROR;
	}
	while (EOF != fscanf(pf, "%d", &e.key)) {
		InsertHash(H, e);
	}
	fclose(pf);
	return OK;
}

/**
 * 打印哈希表中的元素的关键字
 */
void DisplayHashTable(HashTable H)
{
	int i;
	for (i = 0; i < hashsize[H.sizeindex]; i++) {
		if (NULLKEY != H.elem[i].key) {
			printf("%d ", H.elem[i].key);
		}	
	}
}