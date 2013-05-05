#ifndef _RADIX_SORT_H_
#define _RADIX_SORT_H_

#define MAX_NUM_OF_KEY 8	//关键字项数的最大值
#define RADIX 10		//关键字基数
#define MAX_SPACE 1000
typedef int KeysType;
typedef struct {
	KeysType keys[MAX_NUM_OF_KEY];
	int next;
}SLCell;

typedef struct {
	SLCell r[MAX_SPACE];	//静态链表的可利用空间，r[0]为头结点
	int keynum;		//记录的当前关键字个数
	int recnum;		//静态链表的当前长度
}SLList;

typedef int ArrType[RADIX];	//指针数组类型

void Distribute(SLCell r[], int i, ArrType &f, ArrType &e);
int ord(KeysType K);
void Collect(SLCell r[], int i, ArrType f, ArrType e);
int succ(ArrType f, int j);
void RadixSort(SLList &L);

#endif