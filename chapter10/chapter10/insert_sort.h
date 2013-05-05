/* 插入排序 */

#ifndef _INSERT_SORT_H_
#define _INSERT_SORT_H_

/* 静态链表 */
#define SIZE 100
typedef struct {	//表结点类型
	int key;
	int next;
}SLNode;
typedef struct {	//静态链表
	SLNode r[SIZE];	//0号单元为表头结点
	int length;	//链表当前长度
}SLinkList;

Status CreateSqList(SqList &L, char *filename);
void InsertSort(SqList &L);
void BInsertSort(SqList &L);
void TwoInsertSort(SqList &L);
void TableInsertSort(SLinkList &S);
Status CreateSLinkList(SLinkList &S, char *filename);
void Arrang(SLinkList &SL);
void swap(int &i, int &j);
void ShellInsert(SqList &L, int dk);
void ShellSort(SqList &L, int dlta[], int t);

#endif