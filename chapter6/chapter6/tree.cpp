#include <stdio.h>
#include <stdlib.h>

#include "my_headers.h"

/**
 * 算法6.4，按先序顺序构造二叉树
 */
Status CreateBiTree(BiTree &T)
{
	char ch;
	scanf("%c", &ch);
	if (' ' == ch)
		T = NULL;
	else {
		T = (BiTNode *)malloc(sizeof(BiTNode));
		if (!T)
			return ERROR;
		T->data = ch;
		CreateBiTree(T->lchild);	//构造左子树
		CreateBiTree(T->rchild);	//构造右子树
	}
	return OK;
}

/**
 * 打印一个元素
 */
Status display(TElemType e)
{
	printf("%c ", e);
	return OK;
}

/**
 * 算法6.1，先序遍历二叉树，对每个元素调用函数viist
 */
Status PreOrderTraverse(BiTree T, Status (*visit)(TElemType e))
{
	if (T) {
		if (OK == visit(T->data))
			if (OK == PreOrderTraverse(T->lchild, visit))
				if (OK == PreOrderTraverse(T->rchild, visit))
					return OK;
		return ERROR;
	} else
		return OK;
}

/**
 * 中序遍历二叉树，对每个元素调用函数viist
 */
Status InOrderTraverse(BiTree T, Status (*visit)(TElemType e))
{
	if (T) {
		if (OK == InOrderTraverse(T->lchild, visit))
			if (OK == visit(T->data))	
				if (OK == InOrderTraverse(T->rchild, visit))
					return OK;
		return ERROR;
	} else
		return OK;
}

/**
 * 后序遍历二叉树，对每个元素调用函数viist
 */
Status PostOrderTraverse(BiTree T, Status (*visit)(TElemType e))
{
	if (T) {
		if (OK == PostOrderTraverse(T->lchild, visit))
			if (OK == PostOrderTraverse(T->rchild, visit))
				if (OK == visit(T->data))	
					return OK;
		return ERROR;
	} else
		return OK;
}

/**
 * 层序遍历二叉树，利用队列实现
 */
Status LevelOrderTraverse(BiTree T, Status (*visit)(TElemType e))
{
	BiTree p;
	LinkQueue Q;
	InitQueue(Q);
	p = T;
	while (p || !QueueEmpty(Q)) {
		if (p) {
			visit(p->data);
			if (p->lchild)
				EnQueue(Q, p->lchild);
			if (p->rchild)
				EnQueue(Q, p->rchild);
			if (!QueueEmpty(Q))
				DeQueue(Q, p);
			else		//队列为空时，退出while循环
				break;
		}
	}
	return OK;
}

/**
 * 非递归法实现先序遍历二叉树T
 */
Status PreOrderTraverse2(BiTree T, Status (*visit)(TElemType e))
{
	SqStack S;
	BiTree p;
	InitStack(S);
	p = T;
	while (p || !StackEmpty(S)) {
		if (p) {	//访问根指针，左指针进栈
			if (ERROR == visit(p->data))
				return ERROR;
			Push(S, p);
			p = p->lchild;
		} else {
			Pop(S, p);
			p = p->rchild;
		}
	}
	return OK;
}

/**
 * 算法6.2，非递归法实现中序遍历二叉树T
 */
Status InOrderTraverse2(BiTree T, Status (*visit)(TElemType e))
{
	SqStack S;
	BiTree p;
	InitStack(S);
	Push(S, T);		// 根指针进栈
	while (!StackEmpty(S)) {
		while (OK == GetTop(S, p) && p)	//向左走到尽头
			Push(S, p->lchild);
		Pop(S, p);		//空指针退栈
		if (!StackEmpty(S)) {
			Pop(S, p);
			if (ERROR == visit(p->data))
				return ERROR;
			Push(S, p->rchild);
		} // if
	} // while
	return OK;
}

/**
 * 算法6.3，非递归法实现中序遍历二叉树T
 */
Status InOrderTraverse3(BiTree T, Status (*visit)(TElemType e))
{
	SqStack S;
	BiTree p;
	InitStack(S);
	p = T;
	while (p || !StackEmpty(S)) {
		if (p) {	//根指针进栈，遍历左子树
			Push(S, p);
			p = p->lchild;
		}
		else {		//根指针退栈，访问根结点，遍历右子树
			Pop(S, p);
			if (ERROR == visit(p->data))
				return ERROR;
			p = p->rchild;
		} //if
	} //while
	return OK;
}

/**
 * 非递归法实现后序遍历二叉树T
 */
Status PostOrderTraverse2(BiTree T, Status (*visit)(TElemType e))
{
	SqStack S;
	InitStack(S);
	BiTree p;
	int Tag[20];	//标志栈
	int t = 1;
	p = T;
	while (p || !StackEmpty(S)) {
		while (p) {	//向左走到尽头
			Push(S, p);
			p = p->lchild;
			Tag[t++] = 0;
		}

		while (!StackEmpty(S) && 1 == Tag[t-1]) {	//结点标志为1表示右子树已经访问过
			Pop(S, p);
			t--;
			if (ERROR == visit(p->data))
				return ERROR;
		}

		if (!StackEmpty(S)) {	//结点标志为0，则访问右子树，并将结点标志置为1
			Tag[t-1] = 1;
			GetTop(S, p);
			p = p->rchild;
		} 
		else
			break;
	}

	return OK;
}