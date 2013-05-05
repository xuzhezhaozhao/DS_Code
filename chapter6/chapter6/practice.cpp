/* 第六章习题 */

#include <stdio.h>
#include <stdlib.h>

#include "my_headers.h"

/**
 * 习题6.39的树，新建一棵带有双亲域和结点标志的树
 */
Status CreatePTagTree(PTagTree &T)
{
	char ch;
	scanf("%c", &ch);
	if (' ' == ch)
		T = NULL;
	else {
		T = (PTagNode *)malloc(sizeof(BiTNode));
		T->parent = NULL;
		if (!T)
			return ERROR;
		T->data = ch;
		T->mark = Left;	
		CreatePTagTree(T->lchild);	//构造左子树
		CreatePTagTree(T->rchild);	//构造右子树
		printf("");			//我了个去了，把这个去了遍历的时候打印元素的话什么都打印不出来
		if (NULL != T->lchild)
			T->lchild->parent = T;	//双亲域
		if (NULL != T->rchild)
			T->rchild->parent = T;	//双亲域
	}
	return OK;
}

/**
 * 习题6.39，后序遍历，不用栈和递归实现，调用前先执行T->parent = NULL; 还有其他的bug, 有时候在调试的时候结果是对的,
 * 但是打印不出来，不知道是什么原因，应该是新建树的函数有关
 */
Status MyPostOrderTraverse(PTagTree T, Status (*visit)(TElemType e))
{
	PTagTree p, pre;
	p = T;		//p指向根结点
	while (NULL != p) {
		while (p->lchild && Left == p->mark) {		//向左走到尽头
			p->mark = Right;		//下次到达些结点时应该向右走了
			p = p->lchild;
		}
		if (NULL == p->lchild)
			p->mark = Right;

		if (p->rchild && Right == p->mark) {
			p->mark = Visit;
			p = p->rchild;
		} else if (NULL == p->rchild) {
			p->mark = Visit;
		}

		while (Visit == p->mark) {
			if (ERROR == visit(p->data))
				return ERROR;
			p = p->parent;
			if (NULL == p)
				break;
		}
	}
	return OK;
}

/**
 * 习题6.41，求二叉树中位于先序序列中第k个位置结点的值，用value返回该值，
 * 如果第k个位置不存在，则函数返回ERROR，否则返回OK。
 * 进入函数前count的值要置为0，count为遍历过程中计数的变量
 */
Status get_PreOrderValue(BiTree T, int k, int &count, int &value)
{
	if (T) {
		count++;
		if (count == k) {
			value = T->data;
			return OK;
		}
		else {
			if (OK == get_PreOrderValue(T->lchild, k, count, value))	//遍历左子树
				return OK;
			else if (OK == get_PreOrderValue(T->rchild, k, count, value))	//遍历右子树
				return OK;
			else 
				return ERROR;
		}
	} else
		return ERROR;
}

/**
 * 求二叉树中位于中序序列中第k个位置结点的值
 */
Status get_InOrderValue(BiTree T, int k, int &count, int &value)
{
	if (T) {
		if (OK == get_InOrderValue(T->lchild, k, count, value))
			return OK;
		count++;
		if (count == k) {
			value = T->data;
			return OK;
		}
		if (OK == get_InOrderValue(T->rchild, k, count, value))
			return OK;
		return ERROR;
	} else
		return ERROR;
}

/**
 * 求二叉树中位于后序序列中第k个位置结点的值
 */
Status get_PostOrderValue(BiTree T, int k, int &count, int &value)
{
	if (T) {
		if (OK == get_PostOrderValue(T->lchild, k, count, value))
			return OK;
		if (OK == get_PostOrderValue(T->rchild, k, count, value))
			return OK;
		count++;
		if (count == k) {
			value = T->data;
			return OK;
		}
		return ERROR;
	} else
		return ERROR;
}

/**
 * 习题6.42，用递归方法计算二叉树中叶子结点的数目
 */
void get_LeafCount(BiTree T, int &count)
{
	if (T) {
		if (NULL == T->lchild && NULL == T->rchild)	//叶子
			count++;
		else {
			get_LeafCount(T->lchild, count);	//遍历左子树
			get_LeafCount(T->rchild, count);	//遍历右子树
		}
	}
}

/**
 * 习题6.43，用递归法将二叉树的所有结点的左右子树相互交换
 */
void ExchangSubtree(BiTree T)
{
	BiTree temp;
	if (T) {
		if (NULL != T->lchild || NULL != T->rchild) {	//交换左右子树
			temp = T->lchild;	
			T->lchild = T->rchild;
			T->rchild = temp;
			ExchangSubtree(T->lchild);		//交换左子树结点下的左右子树
			ExchangSubtree(T->rchild);		//交换右子树结点下的左右子树
		}
	}
}

/**
 * 习题6.44，求二叉树中以元素值x的结点为根的子树的深度，deep返回树的深度，
 * 若不存在x元素的结点，则返回ERROR，否则返回OK
 */
Status get_NodeDeepth(BiTree T, TElemType x, int &deep)
{
	if (T) {
		if (x == T->data) {
			deep = get_TreeDeepth(T);
			return OK;
		} else {
			if (OK == get_NodeDeepth(T->lchild, x, deep))
				return OK;
			if (OK == get_NodeDeepth(T->rchild, x, deep))
				return OK;
			return ERROR;
		}
	} else
		return ERROR;
}

/**
 * 返回二叉树的深度，递归算法
 */
int get_TreeDeepth(BiTree T)
{
	int ldeep, rdeep;
	if (NULL == T)
		return 0;
	ldeep = get_TreeDeepth(T->lchild);
	rdeep = get_TreeDeepth(T->rchild);
	if (ldeep > rdeep)
		return (ldeep+1);
	return (rdeep+1);
}

/**
 * 删除一棵树，并释放相应的结点空间
 * 注意，不要忘了加&，否则T无法释放
 */
void DestroyTree(BiTree &T)
{
	if (T) {
		DestroyTree(T->lchild);	//先删除左右子树
		DestroyTree(T->rchild);
		free(T);
		T = NULL;
	}
}

/**
 * 习题6.45，对于二叉树中每个元素值为x的结点，删除以它为根的子树，并释放相应结点空间
 */
void DeleteNode(BiTree &T, TElemType x)
{
	if (T) {
		if (T->data == x)
			DestroyTree(T); 
		else {
			DeleteNode(T->lchild, x);
			DeleteNode(T->rchild, x);
		}
	}
}

/**
 * 习题6.46，用递归法复制一棵二叉树T到Tc
 */
void CopyTree(BiTree T, BiTree &Tc)
{
	if (T) {
		Tc = (BiTree)malloc(sizeof(BiTNode));
		Tc = T;
		Tc->data = T->data;
		Tc->lchild = T->lchild;
		Tc->rchild = T->rchild;
		if (T->lchild)		//复制左子树
			CopyTree(T->lchild, Tc->lchild);
		if (T->rchild)		//复制右子树
			CopyTree(T->rchild, Tc->rchild);
	}
}

/**
 * 得到一棵从根到指定结点p的路径树T，删除多余的节点;
 */
Status PathTree(BiTree &T, BiTree p)
{
	if (T) {
		if (T == p) {
			if (T->lchild)
				DestroyTree(T->lchild);
			if (T->rchild)
				DestroyTree(T->rchild);
			return OK;
		} else {
			if (OK == PathTree(T->lchild, p))	//当前结点不是，就到左子树中寻找
				return OK;
			else					//左子树中也找不到就删除左子树
				DestroyTree(T->lchild);
			if (OK == PathTree(T->rchild, p))
				return OK;
			else
				DestroyTree(T->rchild);
			return ERROR;
		}
	} else
		return ERROR;
}

/**
 * 习题6.47，层序遍历二叉树，在tree.cpp中实现了
 */

/**
 * 习题6.48，*root为根结点，*p和*q为二叉树中两个结点，求距离它们最近的共同祖先的算法
 * m 结点指向其共同祖先的位置
 */
Status get_MinComAncester(BiTree root, BiTree p, BiTree q, BiTree m)
{

	return OK;
}

/**
 * 习题4.49，非递归法判定给定二叉树是否为完全二叉树
 */
bool isCompleteBiTree(BiTree T)
{
	LinkQueue Q;
	InitQueue(Q);
	BiTree p;
	int flag = 1;	//是否遍历到达最后一层的标志，到达最后一层则flag置0
	p = T;
	while (p || !QueueEmpty(Q)) {
		if (p) {
			if (p->lchild && p->rchild && 1 == flag) {	//左右孩子都存在
				EnQueue(Q, p->lchild);
				EnQueue(Q, p->rchild);
			} else if (p->lchild && !p->rchild && 1 == flag) {	//左孩子存在，右孩子不存在,到达最后一层
				flag = 0;
				EnQueue(Q, p->lchild);
			} else if (!p->lchild && p->rchild)	//左孩子不存在，右孩子存在,结束
				return false;
			else if (!p->lchild && !p->rchild)	//左右孩子都不存在
				flag = 0;
			else
				return false;

			if (!QueueEmpty(Q))
				DeQueue(Q, p);
			else
				return true;
		}
	}
	return true;
}

/**
 * 习题6.50，以三元组（F, C, L/R）的形式创建一棵二叉树，如^AL ABL ^^L创建以A为根的树
 */
Status MyCreateTree(BiTree &T)
{
	char c;
	BiTree p, q;
	BiTree R[20];		//保存已经创建了的结点
	int len = 0;		//结点数组的指针
	c = getchar();
	while (' ' == c || '\t' == c || '\n' == c)	//过滤空字符
		c = getchar();
	if ('^' == c) {				//创建根
		c = getchar();
		if ('^' != c) {
			T = (BiTree)malloc(sizeof(BiTNode));
			if (!T)
				return ERROR;	//分配失败
			R[len++] = T;		//将结点存入结点数组
			T->data = c;
			T->lchild = NULL;
			T->rchild = NULL;
			c = getchar();
		} else {
			T = NULL;
			return OK;	//创建空树
		}
	} else				//输入错误
		return ERROR;

	while (1) {			//创建子树
		c = getchar();
		while (' ' == c || '\t' == c || '\n' == c)	//过滤空字符
			c = getchar();
		if ('^' == c)	//输入结束
			return OK;
		if (ERROR == SearchNode(R, len, c, p))		//搜索结点数组得到指定的父结点
			return ERROR;
		c = getchar();		//得到三元组第二个字符
		q = (BiTree)malloc(sizeof(BiTNode));		//为子结点分配空间
		if (!q)
			return ERROR;	//分配失败
		R[len++] = q;		//将结点加入结点数组中
		q->data = c;
		q->lchild = NULL;
		q->rchild = NULL;
		c = getchar();		//得到三元组第三个字符
		if ('L' == c || 'l' == c)
			p->lchild = q;
		else if ('R' == c || 'r' == c)
			p->rchild = q;
		else			//输入错误
			return ERROR;
	}
}

/**
 * 在长度为len的结点数组中搜索元素值c的结点，并以p返回，确保没有元素值相同的结点
 * 找到返回OK，否则返回ERROR
 */
Status SearchNode(BiTree R[], int len, char c, BiTree &p)
{
	int i;
	for (i=0; i<len; i++)
		if (c == R[i]->data) {
			p = R[i];
			return OK;
		}
	return ERROR;
}

/**
 * +、－、*、/优先级判断,与P53表中的不一样
 */
char PrecedeTree(char c1, char c2)
{
	switch (c1) {
	case '+':
	case '-':
		switch (c2) {
		case '*':
		case '/':
			return '<';
		default:
			break;
		}
		break;
	case '*':
	case '/':
		switch (c2) {
		case '+':
		case '-':
			return '>';
		default:
			break;
		}
		break;
	default:
		break;
	}
	return ' ';
}

/**
 * 习题6.51，输出以二叉表示算术表达式，并加上适当的括号，如课本P129页图6.9
 */
void OutputExpression(BiTree T)
{
	if (T) {
		if (isOpt(T->data)) {		//当该结点是运算符时
			if (T->lchild && '>' == PrecedeTree(T->data, T->lchild->data)) {	//判断算符优先级
				printf("(");
				OutputExpression(T->lchild);
				printf(")");
			} else
				OutputExpression(T->lchild);
			printf("%c", T->data);
			if (T->rchild && '>' == PrecedeTree(T->data, T->rchild->data)) {
				printf("(");
				OutputExpression(T->rchild);
				printf(")");
			} else
				OutputExpression(T->rchild);
		} else {			//该结点为非运算符时则直接打印出来
			printf("%c", T->data);
		}
	}
}

/**
 * 判断一个字符是否是+,-,*,/运算符，是返回true,否则返回false
 */
bool isOpt(char c)
{
	if ('+' == c || '-' == c || '*' == c || '/' == c)
		return true;
	return false;
}