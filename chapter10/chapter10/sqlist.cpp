#include <stdio.h>
#include <stdlib.h>

#include "type.h"
#include "sqlist.h"

Status InitList_Sq(struct SqList &L)
{ 
	//构造一个空的线性表L
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(struct SqList));
	if(!L.elem)
		return (OVERFLOW);			//存储分配失败
	L.length = 0;					// 空表长度为0
	L.listsize = LIST_INIT_SIZE;	// 初始存储容量
	return OK;
} // InitList_Sq

void DestoryList_Sq(struct SqList &L)
{
	//销毁线性表L
	//要求线性表L存在
	free(L.elem);
	L.elem = NULL;
} //DestoryList_Sq_Sq

void ClearList_Sq(struct SqList &L)
{
	//将L重置为空表
	//要求线性表L存在
	L.length = 0;
} //ClearList_Sq

Status ListEmpyt_Sq(struct SqList L)
{
	//若L为空表，返回TRUE，否则返回FALSE
	//要求线性表L存在
	if(0 == L.length)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
} // ListEmpyt_Sq

Status ListLength_Sq(struct SqList L)
{
	//要求线性表已存在
	//返回L中数据元素个数
	return L.length;
} //ListLength_Sq

void GetElem_Sq(struct SqList L, int i, ElemType &e)
{
	//要求线性表存在，1<=i<=ListLength_Sq(L)
	//e返回L中第i个数据元素的值
	e = *(L.elem + i - 1);
} //GetElem_Sq

Status compare_equal_Sq(ElemType e1, ElemType e2)
{
	//判断两个数据元素是否相等，相等返回TRUE，不等返回FALSE
	if(e1 == e2)
		return TRUE;
	else
		return FALSE;
} //compare_equal_Sq

Status LocateElem_Sq(struct SqList L, ElemType e, Status (*compare)(ElemType, ElemType))
{
	//线性表L已存在，compare()是数据元素判定函数
	//返回L中第一个与e满足关系的compare()的数据元素的位序。若这样的数据元素不存在，返回0
	ElemType * p = L.elem;
	int i; // 位序
	for(i=1; i<=L.length; i++)
	{
		if(compare(e, *(p+i-1)))
		{
			return i;
		}
	}
	return 0;
} //LocateElem_Sq

Status PriorElem_Sq(struct SqList L, ElemType cur_e, ElemType &pre_e)
{
	//要求线性表L存在
	//若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，否则操作失败，pre_e无定义
	int pos;
	pos = LocateElem_Sq(L, cur_e, compare_equal_Sq);
	if(!pos || 1 == pos)  // 元素cur_e在L中不存在或为第一个
		return NOTEXIT;
	else
		return *(L.elem+pos-2);
} //PriorElem_Sq


Status NextrElem_Sq(struct SqList L, ElemType cur_e, ElemType &next_e)
{
	//要求线性表L存在
	//若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后驱，否则操作失败，next_e无定义
	int pos;
	pos = LocateElem_Sq(L, cur_e, compare_equal_Sq);
	if(!pos || L.length == pos)  // 元素cur_e在L中不存在或为最后一个
		return NOTEXIT;
	else
		return *(L.elem+pos);
} //NextrElem_Sq


void ListInsert_Sq(struct SqList &L, int i, ElemType e)
{
	//要求线性表存在，1<=i<=ListLength_Sq(L)+1
	//在第i个位置之前插入数据元素e, L的长度加1

	int j;
	ElemType * newbase;
	if(L.length+2 > L.listsize)	//因为0号元素未用，所以是加2
	{
		newbase = (ElemType *)realloc(L.elem, 
			(L.listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase)
			exit(OVERFLOW);   //存储分配失败
		L.elem = newbase;  // 新基址
		L.listsize += LISTINCREMENT;  // 增加存储容量
	}
	for(j = L.length+1; j >=i ; j--)
	{
		*(L.elem+j) = *(L.elem+j-1);
	}
	*(L.elem+i-1) = e;
	L.length++;   // 表长加1
} //ListInsert_Sq

void ListDelete_Sq(struct SqList &L, int i, ElemType &e)
{
	//线性表存在且非空，1<=i<=ListLength_Sq(L)
	//删除L的第i个元素，并用e返回其值，L的长度减1
	int j;
	e = *(L.elem+i-1);
	for(j=i; j<L.length; j++)
	{
		*(L.elem+j-1) = *(L.elem+j);
	}
	L.length--;
} //ListDelete_Sq

Status ListTraverse_Sq(struct SqList L, Status (*visit)(ElemType))
{
	//要求线性表存在
	//依次对L的每个元素调用函数visit(), 一旦visit()失败，则操作失败，返回FALSE,否则返回TRUE
	int i;
	for(i=1; i<=L.length; i++)
	{
		if(!visit(*(L.elem+i)))
			return FALSE;	    
	}
	return TRUE;
} // ListTraverse_Sq

Status visit_display_Sq(ElemType e)
{
	printf("%d ", e);
	return TRUE;
} //visit_display_Sq



//算法


//算法2.1
void unionList_Sq(struct SqList &La, struct SqList Lb)
{
	//将Lb中存在但La中不存在的元素插入到La中
	int La_len = ListLength_Sq(La);
	int Lb_len = ListLength_Sq(Lb);
	int i;
	ElemType e;
	for(i=1; i<=Lb_len; i++)
	{
		GetElem_Sq(Lb, i, e);    // 取第不个元素赋给e
		if(!LocateElem_Sq(La, e, compare_equal_Sq))
		{  
			ListInsert_Sq(La, ++La_len, e);  
		}
	}
}  //unionList_Sq

//算法2.2
void MergeList_Sq(struct SqList La, struct SqList Lb, struct SqList &Lc)
{
	//已知线性表La和Lb中数据元素按值非递减排列
	//归并La和Lb得到新的线性表Lc,Lc的数据元素也按值非递减排列
	int i, j, k, ai, bj;
	int La_len, Lb_len;
	InitList_Sq(Lc);
	i = j = k = 1;
	La_len = ListLength_Sq(La);
	Lb_len = ListLength_Sq(Lb);
	while(i<=La_len && j<=Lb_len)
	{
		//La, Lb为非空表
		GetElem_Sq(La, i, ai);
		GetElem_Sq(Lb, j, bj);
		if(ai <= bj)
		{
			ListInsert_Sq(Lc, k++, ai);
			++i;
		}
		else
		{
			ListInsert_Sq(Lc, k++, bj);
			++j;
		}
	}
	while(i <= La_len)
	{
		GetElem_Sq(La, i++, ai);
		ListInsert_Sq(Lc, k++, ai);
	}
	while(j <= Lb_len)
	{
		GetElem_Sq(Lb, j++, bj);
		ListInsert_Sq(Lc, k++, bj);
	}
} //MergList

//算法2.3，2.4，2.5，2.6，2.7
//前面实现了


