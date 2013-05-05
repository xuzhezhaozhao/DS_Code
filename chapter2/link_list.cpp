//线性链表的构造及算法

#include <stdio.h>
#include <stdlib.h>

#include "sqlist.h"
#include "link_list.h"

void InitList_L(struct LNode * &L)
{
	//构造一个空的线性链表L
	L = (struct LNode *) malloc (sizeof(LNode));
	L->next = NULL;
}

void DestoryList_L(struct LNode * &L)
{
	//销毁表L
	free(L);
	L = NULL;
}

void ClearList_L(struct LNode * &L)
{
	//将表L重置为空表
	L->next = NULL;
}

bool ListEmpty_L(struct LNode * &L)
{
	//判断是否为空表，是返回true, 否则返回false
	if (NULL == L->next)
		return true;
	else
		return false;
}

int ListLength_L(struct LNode * &L)
{

	int len = 0; // 计数
	struct LNode *p = L->next;  // p指向第一个结点
	while (NULL != p) {
		len++;
		p = p->next;
	}
	return len;
}

//算法2.8
Status GetElem_L(struct LNode * &L, int i, ElemType &e)
{
	//L为带头结点的单链表头指针
	//当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR
	struct LNode *p = L->next;  // p指向第一个结点
	int j = 1;  // j为计数器
	while(p != NULL && j < i) {
		p = p->next;
		j++;
	}

	if(p == NULL || j > i)
		return ERROR;
	e = p->data;
	return OK;
} // GetElem_L

int LocateElem_L(struct LNode * &L, ElemType e, Status (*compare)(ElemType, ElemType))
{
	//线性表L已存在，compare()是数据元素判定函数
	//返回L中第一个与e满足关系的compare()的数据元素的位序。若这样的数据元素不存在，返回0	//返回L中第一个与有满足关系的数据元素

	struct LNode *p = L->next;  // p指向第一个结点
	int i = 0;  // 位序
	while (NULL != p) {
		i++;
		if (compare(e, p->data))
			return i;
		p = p->next;
	}
	return 0;
}

Status PriorElem_L(struct LNode * &L, ElemType cur_e, ElemType &pre_e)
{
	//要求线性表L存在
	//若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，否则操作失败，pre_e无定义
	
	int i = 0;
	struct LNode *p = L->next;
	while (NULL != p) {
		i = LocateElem_L(L, cur_e, compare_equal_Sq);
		if (0 != i && 1 != i) {
			GetElem_L(L, i-1, pre_e);
			return OK;
		}
		p = p->next;
	}
	return ERROR;
}

Status NextElem_L(struct LNode * &L, ElemType cur_e, ElemType &next_e)
{
	//要求线性表L存在
	//若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后驱，否则操作失败，next_e无定义
	
	int i = 0;
	struct LNode *p = L->next;
	while (NULL != p) {
		i = LocateElem_L(L, cur_e, compare_equal_Sq);
		if (i<ListLength_L(L)) {
			GetElem_L(L, i+1, next_e);
			return OK;
		}
		p = p->next;
	}
	return ERROR;
}

Status ListInsert_L(struct LNode * &L, int i, ElemType e)
{
	//要求线性表存在，1<=i<=ListLength_Sq(L)+1
	//在第i个位置之前插入数据元素e
	struct LNode *p;
	struct LNode *newNode;
	int j;
	p = L;
	j = 0;
	while (NULL != p && j < i-1) {  // 寻找第i-1个结点
		p = p->next;
		++j;
	}
	if (NULL == p || j > i-1)
		return ERROR;
	newNode = (struct LNode *)malloc(sizeof(LNode));  // 生成新结点
	newNode->data = e;
	newNode->next = p->next;
	p->next = newNode;
	return OK;
} //ListInsert_L

Status ListDelete_L(struct LNode * &L, int i, ElemType &e)
{
	//线性表存在且非空，1<=i<=ListLength_Sq(L)
	//删除L的第i个元素，并用e返回其值
	struct LNode *p;
	struct LNode *del_p;
	int j;
	p = L;
	j = 0;
	while (NULL != p->next && j < i-1) {  // 寻找第i个结点
		p = p->next;
		++j;
	}
	if (NULL == p->next || j > i-1)
		return ERROR;
	del_p = p->next;   // del_p指向被删除的结点
	p->next = del_p->next;
	e = del_p->data;
	free(del_p);
	del_p = NULL;
	return OK;
} // ListDelete_L

Status ListTraverse_L(struct LNode * &L, Status (*visit)(struct LNode * &))
{
	//要求线性表存在
	//依次对L的每个元素调用函数visit(), 一旦visit()失败，则操作失败，返回FALSE,否则返回TRUE

	struct LNode *p;
	p = L->next;   // p指向第一个结点L->next; 
	while (NULL != p) {
		if(ERROR == visit(p))
			return ERROR;
		p = p->next;
	}
	return OK;
}

Status visit_display_L(struct LNode * &L)
{
	printf("%d ", L->data);
	return OK;
}


//算法
//算法2.11
void CreateList_L(struct LNode * &L, int n)
{
	//逆位序输入n个元素的值，建立带表头结点的单链表
	int i;
	struct LNode *p;
	L= (struct LNode *) malloc (sizeof(LNode));
	L->next = NULL;
	for (i=n; i>0; i--) {
		p = (struct LNode *) malloc (sizeof(LNode));  // 生成新结点
		scanf("%d", &p->data);
		p->next = L->next;
		L->next = p;
	}
} // CreatList_L

//算法2.12
void MergeList_L(struct LNode * &La, struct LNode * &Lb, struct LNode * &Lc)
{
	//La, Lb非递减排列
	//归并到Lc中也按非递减排列
	struct LNode * pa = La->next; // pa指向La的第一个结点
	struct LNode * pb = Lb->next; // pb指向Lb的第一个结点
	struct LNode * pc = Lc = La;

	while (NULL != pa && NULL != pb) {
		if (pa->data <= pb->data) {
			pc->next = pa;
			pc = pc->next;
			pa = pa->next;
		} else {
			pc->next = pb;
			pc = pc->next;
			pb = pb->next;
		}
	}

	if (NULL == pa)
		pc->next = pb;
	else
		pc->next = pa;
	free(Lb);
	Lb = NULL;
}