#include <stdio.h>
#include <stdlib.h>

#include "my_headers.h"


/**
 * 按先序顺序构造二叉树
 */
Status CreateBiThrTree(BiThrTree &T)
{
	char ch;
//	scanf("%c", &ch);
	ch = getchar();
	if (' ' == ch)
		T = NULL;
	else {
		T = (BiThrNode *)malloc(sizeof(BiThrNode));
		if (!T)
			return ERROR;
		T->data = ch;
		T->LTag = Link;
		T->RTag = Link;
		CreateBiThrTree(T->lchild);	//构造左子树
		CreateBiThrTree(T->rchild);	//构造右子树
	}
	return OK;
}

/**
 * 算法6.5，T指向头结点，头结点的左链lchild指向根结点，右链指向遍历的最后一个结点，中序遍历二叉线索树的非递归算法
 */
Status InOrderTraverse_Thr(BiThrTree T, Status (*visit)(TElemType e))
{
	BiThrTree p;
	p = T->lchild;		//p指向根结点
	while (p != T) {	//空树或遍历结束时，p == T
		while (Link == p->LTag)
			p = p->lchild;	// 走到左子树的尽头
		if (ERROR == visit(p->data))
			return ERROR;
		while (Thread == p->RTag && p->rchild != T) {	//右链为线索，指向后继结点，当p为最后一个结点时，p->rchild == T (头结点)
			p = p->rchild;
			if (ERROR == visit(p->data))		//访问后继结点
				return ERROR;
		}
		p = p->rchild;		//右链不是线索时，将p指向其右子树，或者p指向头结点，表明遍历结束
	}
	return OK;
}
BiThrTree pre;
/**
 * 算法6.6，中序遍历二叉树T，并将其中序线索化，Thrt指向头结点
 */
Status InOrderThreading(BiThrTree &Thrt, BiThrTree T)
{
	printf("");	//不知道什么原因，不加这一句就什么都显示不出来，真他妈的奇怪
	if (!(Thrt = (BiThrNode *)malloc(sizeof(BiThrTree)) ))	//建头结点
		return ERROR;
	Thrt->LTag = Link;
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;
	if (!T)
		Thrt->lchild = Thrt;		//T为空树，则头结点左指针指向头结点
	else {
		Thrt->lchild = T;		//头结点左链指向根结点
		pre = Thrt;			//pre初始时指向头结点
		InThreading(T);		//中序遍历进行线索化
		pre->rchild = Thrt;		//最后一个结点线索化，最后一个结点的右链指向头结点
		pre->RTag = Thread;
		Thrt->rchild = pre;		//头结点的右链指向最后一个遍历的结点
	}
	return OK;
}

/**
 * 算法6.7
 */
void InThreading(BiThrTree p)
{
	if (p) {
		InThreading(p->lchild);	//左子树线索化
		if (!p->lchild) {	//左链为空时，前继线索
			p->LTag = Thread;
			p->lchild = pre;	//pre为中序遍历访问的前一个结点
		}
		if (!pre->rchild) {	//前一个结点的右链为空时，后继线索
			pre->RTag = Thread;
			pre->rchild = p;
		}
		pre = p;		//保持pre指向p的前驱
		InThreading(p->rchild);	//右子树线索化
	}
}