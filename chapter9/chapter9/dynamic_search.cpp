#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "my_headers.h"

/**
 * 算法9.5（a），在根指针所指的二叉排序树中递归地查找关键字等于key的数据元素,
 * 返回空表示没有找到，pr返回空，否则返回指向找到的结点的指针, pr返回找到的结点的父结点.
 */
BiTNode* SearchBSTa(BiTree T, KeyType key, BiTree f, BiTree &pr)
{
	BiTNode *p;
	if (NULL == T) {					//查找结束, 没有找到
		pr = NULL;
		return NULL;
	} else if (EQ(key, T->data.key)) {			//查找结束，找到
		pr = f;
		return (T);
	} else if (LT(key, T->data.key)) {			//到左子树中寻找
		p = SearchBSTa(T->lchild, key, T, pr);
		return (p);
	} else {						//到右子树中寻找
		p = SearchBSTa(T->rchild, key, T, pr);
		return (p);
	}
}

/**
 * 算法9.5（b）, 在算法9.5（a）的基础上增加插入没有找到的元素的功能;
 * 若查找成功，p返回找到的数据元素结点，并返回true，否则指针p指向查找路径上访问的最后
 * 一个结点，并返回false，指针f指向T的双亲，初始时为NULL
 */
bool SearchBSTb(BiTree T, KeyType key, BiTree f, BiTree &p)
{
	if (NULL == T) {			//表示没有找到，查找失败
		p = f;
		return false;
	} else if (EQ(key, T->data.key)) {	//查找成功
		p = T;
		return true;
	} else if (LT(key, T->data.key)) {	//到左子树查找
		return (SearchBSTb(T->lchild, key, T, p));
	} else {				//到右子树查找
		return (SearchBSTb(T->rchild, key, T, p));
	}
}

/**
 * 算法9.6，查找并插入不存在的元素，当二叉排序树T中不存在关键字等于e.key的数据元素时，
 * 插入e并返回true，否则返回false.
 */
bool InsertBST(BiTree &T, ElemType e)
{
	BiTree p;
	BiTNode *s;
	if (!SearchBSTb(T, e.key, NULL, p)) {		//查找不成功
		s = (BiTNode *)malloc(sizeof(BiTNode));	//新建一个要插入的结点
		s->data = e;
		s->lchild = NULL;
		s->rchild = NULL;
		if (NULL == p) {			//新插入的结点为根结点
			T = s;
		} else if (LT(e.key, p->data.key)) {	//插入到左子树
			p->lchild = s;
		} else {				//插入到右子树
			p ->rchild = s;
		}
		return true;
	} else {
		return false;
	}
}

/**
 * 算法9.7，若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素结点，
 * 并返回true，否则返回false.
 */
bool DeleteNodeBST(BiTree &T, KeyType key)
{
	BiTree pr, p;
	pr = NULL;
	p = SearchBSTa(T, key, NULL, pr);
	if (NULL != p) {				//查找成功
		DeleteNode(T, p, pr);
		return true;
	} else {					//查找失败
		return false;
	}
}

/**
 * 算法9.8，从二叉排序树T中删除结点p，并重接它的左或右子树, pr指向p的父结点。
 */
Status DeleteNode(BiTree &T, BiTree &p, BiTree pr)
{
	BiTree s;
	if (NULL == p->lchild && NULL == p->rchild) {		//左右子树均空
		if (pr != NULL) {				//p结点不为根结点时
			if (pr->lchild == p) {
				pr->lchild = NULL;
			} else {
				pr->rchild = NULL;
			}
		}
		free(p);
		p = NULL;
	} else if (NULL != p->lchild && NULL == p->rchild) {	//左子树不空，右子树空
		if (pr != NULL) {
			if (pr->lchild == p) {
				pr->lchild = p->lchild;
			} else {
				pr->rchild = p->lchild;
			}
		} else {					//p结点为根结点时
			T = p->lchild;
		}
		
		free(p);
		p = NULL;
	} else if (NULL == p->lchild && NULL != p->rchild) {	//左子树空，右子树不空
		if (pr != NULL) {
			if (pr->lchild == p) {
				pr->lchild = p->rchild;
			} else {
				pr->rchild = p->rchild;
			}
		} else {
			T = p->rchild;
		}
		
		free(p);
		p = NULL;
	} else {				//左右子树都不空
		s = p->lchild;
		while (NULL != s->rchild) {		//s走到最右边就是p的中序遍历的直接前驱了
			s = s->rchild;
		}

		s->rchild = p->rchild;		//连接p的左右子树
		if (pr != NULL) {
			if (pr->lchild == p) {
				pr->lchild = p->lchild;
			} else {
				pr->rchild = p->lchild;
			}
		} else {
			T = p->lchild;
		}
		
		free(p);
		p = NULL;
	}

	return OK;
}

/**
 * 算法9.9，对以*p为根的二叉排序树作右旋处理，处理之后p指向新的树根结点，
 * 即旋转处理之前的左子树的根结点。
 */
void R_Rotate(BSTree &p)
{
	BSTree lc;
	lc = p->lchild;			//lc指向p的左子树
	p->lchild = lc->rchild;		//lc的右子树挂在p的左子树下
	lc->rchild = p;			//p挂在lc的左子树下
	p = lc;				//p指向新的根结点
}

/**
 * 算法9.10，左旋操作
 */
void L_Rotate(BSTree &p)
{
	BSTree rc;
	rc = p->rchild;
	p->rchild = rc->lchild;
	rc->lchild = p;
	p = rc;
}

/**
 * 算法9.11，若平衡的二叉排序树T中不存在和e有相同关键字的结点，则插入一个数据元素为e
 * 的结点，并返回1，否则返回0，若因此插入而使二叉排序树失去平衡，则作平衡旋转处理, 
 * taller指示树的深度是否增加。用递归的方法寻找要插入的位置，并检测平衡度以做出相应的
 * 旋转的变化，但因为旋转之后树的深度其实和插入前是没有变化的，
 * 所以整个递归过程中其实只有最小非平衡子树需要作旋转平衡操作，其余结点都无需作旋转操作。
 */
Status InsertAVL(BSTree &T, ElemType e, bool &taller)
{
	if (NULL == T) {	//空树，插入结点e，树深度增加，置taller为true
		T = (BSTree)malloc(sizeof(BSTNode));
		T->data = e;
		T->lchild = NULL;
		T->rchild = NULL;
		T->bf = EH;
		taller = true;
	} else {
		if (EQ(e.key, T->data.key)) {		//树中存在该元素，则不再插入
			taller = false;
			return 0;
		} else if (LT(e.key, T->data.key)) {		//元素小于根结点，则应在根结点左子树中继续寻找
			if (0 == InsertAVL(T->lchild, e, taller)) {	//左子树中有该元素，则未插入
				return 0;
			} else {		//元素插入到左子树中
				if (taller) {	//已插入以左子树且左子树深度增加，子树不增高的情况不需要考虑
					switch (T->bf) {	//检查T的平衡度
					case LH:		//原本左子树比右子树高，需要作左平衡处理
						LeftBalance(T);
						taller = false;
						break;
					case EH:		//原本左右子树等高，现因左子树增高使树增高
						T->bf = LH;
						taller = true;
						break;
					case RH:		//原本右子树高，现左右子树等高，树高不增加
						T->bf = EH;
						taller = false;
						break;
					}
				}
			}
		} else {			//应在T的右子树中进行搜索
			if (0 == InsertAVL(T->rchild, e, taller)) {	//未插入
				return 0;
			} else {
				if (taller) {		//已插入到右子树且右子树长高
					switch (T->bf) {	//检查T的平衡度
					case LH:
						T->bf = EH;
						taller = false;
						break;
					case EH:
						T->bf = RH;
						taller = true;
						break;
					case RH:	//需作右平衡处理
						RightBalance(T);
						taller = false;
						break;
					}
				}
			}
		}
	}

	return 1;
}

/**
 * 算法9.12，对以指针T所指结点为根的二叉树作左平衡处理，本算法结束时，指针T指向
 * 新的根结点；
 * 左平衡操作是指当T的左子树的深度与右子树深度之差大于2时所需要作出的操作。
 */
void LeftBalance(BSTree &T)
{
	BSTree lc, rd;
	lc = T->lchild;		//lc指向T的左子树根结点
	switch (lc->bf) {	//检查T的左子树的平衡度
	case LH:		//新结点插入在T的左孩子的左子树上，要作单右旋处理
		T->bf = lc->bf = EH;
		R_Rotate(T);
		break;
	case RH:		//新结点插入在T的左孩子的右子树上，要作双旋处理
		rd = lc->rchild;	//rd指向T的左孩子的右子树的根
		switch (rd->bf) {	//修改T及其左孩子的平衡因子
		case LH:
			T->bf = RH;
			lc->bf = EH;
			break;
		case EH:
			T->bf = EH;
			lc->bf = EH;
			break;
		case RH:
			T->bf = EH;
			lc->bf = LH;
			break;
		}
		rd->bf = EH;
		L_Rotate(T->lchild);
		R_Rotate(T);
	}
	
}

/**
 * 对以指针T所指结点为根的二叉树作右平衡处理，本算法结束时，指针T指向新的根结点
 */
void RightBalance(BSTree &T)
{
	BSTree rc, ld;
	rc = T->rchild;		//rc指向T的右子树根结点
	switch (rc->bf) {	//检查T的右子树的平衡度
	case RH:		//新结点插入在T的右孩子的右子树上，要作单左旋处理
		T->bf = rc->bf = EH;
		L_Rotate(T);
		break;
	case LH:		//新结点插入在T的右孩子的左子树上，要作双旋处理
		ld = rc->lchild;	//ld指向T的右孩子的左子树根结点
		switch (ld->bf) {
		case LH:
			T->bf = EH;
			rc->bf = RH;
			break;
		case EH:
			T->bf = EH;
			rc->bf = EH;
			break;
		case RH:
			T->bf = LH;
			rc->bf = EH;
			break;
		}
		ld->bf = EH;
		R_Rotate(T->rchild);
		L_Rotate(T);
	}
}

/**
 * 算法9.13，在m阶B-树T上查找关键字K，返回结果（pt, i, tag），若查找成功，
 * 则特征值tag = 1，指针pt所指结点中第i个关键字等于K，否则特征值tag = 0，
 * 等于K的关键字应插入在指针pt所指结点中第i和第i+1个关键字之间。
 */
Result SearchBTree(BTree T, KeyType K)
{
	int i;
	Result r;
	BTree p, q;
	bool found;
	p = T;
	q = NULL;
	i = 0;
	found = false;
	while (p != NULL && !found) {
		i = Search(p, K);
		if (i > 0 && K == p->Key[i]) {	//找到待查关键字
			found = true;
		} else {
			q = p;
			p = p->ptr[i];
		}
	}
	if (found) {	//查找成功
		r.pt = p;
		r.i = i;
		r.tag = 1;
	} else {	//查找不成功，返回K的插入位置信息
		r.pt = q;
		r.i = i;
		r.tag = 0;	
	}
	return r;
}

/**
 * 在p->Key[1...keynum]中查找i，使p->Key[i] <= K < p->Key[i+1]，当K < p->Key[1]时，
 * i = 0, 返回找到的i.
 */
int Search(BTree p, KeyType K)
{
	int i, j;
	if (K < p->Key[1]) {
		i = 0;
	} else if (K >= p->Key[p->keynum]) {
		i = p->keynum;	
	} else {
		for (j = 1; j <= (p->keynum) - 1; j++) {
			if (K >= p->Key[j] && K < p->Key[j + 1]) {
				i = j;
				break;
			}
		}
	}
	return i;
}

/**
 * 算法9.14，首先查找m阶B树上是否有关键字K，有则不插入，返回0，否则在m阶B-树插入关键字K
 * 并返回1，若引起结点过大，则沿双亲链进行必要的结点分裂调整，使T仍是m阶B-树。
 */
Status InsertBTree(BTree &T, KeyType K)
{
	int s;				// 要插入到父结点中的关键字的位置
	KeyType x = K;
	BTree ap = NULL;		//分裂出的结点
	bool finished = false;		//分裂是否完成标志
	Result res;
	BTree q;
	res = SearchBTree(T, K);
	int i;
	q = res.pt;
	i = res.i;
	if (1 == res.tag) {
		return 0;
	} else {
		while (q != NULL && !finished) {	//要插入的结点不为空且分裂还没有完成
			Insert(q, i, x, ap);	//插入关键字x及指针ap到q->Key[i+1], q->ptr[i+1]
			if (q->keynum < m) {		//结点大小合适，结束分裂
				finished = true;
			} else {			//分裂结点*q
				s = (int) ceil(m / 2.0);	//中间关键字位置
				split(q, s, ap);		//将s前的关键字保留在q中，s后面的关键字分裂出去到新的结点ap中
				x = q->Key[s];
				q = q->parent;
				if (q != NULL) {
					i = Search(q, x);	//在双亲结点中查找插入x的位置
				}
			}
		}

		if (!finished) {		//T是空树，或者根结点已分裂
			NewRoot(T, q, x, ap);	//生成含信息(T, x, ap)的新的根结点*T，原T和ap为子树指针
		}
		return 1;
	}
}

/**
 * 将关键字x和指针ap分别插入到p->Key[i+1]和p->ptr[i+1]中，注意结点关键字大小
 * p->keynum要加1.
 */
Status Insert(BTree p, int i, KeyType x, BTree ap)
{
	int j;
	for (j = p->keynum; j >= i + 1 ; j--) {
		p->Key[j + 1] = p->Key[j];
		p->ptr[j + 1] = p->ptr[j];		
	}
	p->Key[i + 1] = x;
	p->ptr[i + 1] = ap;
	p->keynum++;
	if (ap != NULL) {
		ap->parent = p;
	}
	return OK;
}

/**
 * 分裂结点*p，以s位置为分界分裂，ap->Key[] = p->Key[s+1...m], 
 * ap->ptr[] = p->ptr[s...m], p->Key[] = p->Key[1...s-1], 
 * p->ptr[] = p->ptr[0...s-1]，注意修改新建结点ap的父结点。
 */
Status split(BTree p, int s, BTree &ap)
{
	int i, j;
	p->keynum = s - 1;

	ap = (BTree)malloc(sizeof(BTNode));	//分配一个新结点
	for (i = s + 1, j = 1; i <= m; i++, j++) {
		ap->Key[j] = p->Key[i];
	}
	for (i = s, j = 0; i <= m; i++, j++) {
		ap->ptr[j] = p->ptr[i];
		if (ap->ptr[j] != NULL) {		//更新结点的父结点，这一个问题debug了好久，mark一个
			ap->ptr[j]->parent = ap;
		}
	}
	ap->keynum = m - s;
	ap->parent = p->parent;

	return OK;
}

/**
 * 生成新的根结点, 根结点信息为Key[1] = x, ptr[0, 1] = (q, ap)
 */
Status NewRoot(BTree &T, BTree q, int x, BTree ap)
{
	BTree root;
	root = (BTree)malloc(sizeof(BTNode));
	root->Key[1] = x;
	root->ptr[0] = T;
	root->ptr[1] = ap;
	root->keynum = 1;
	root->parent = NULL;
	if (T != NULL) {
		T->parent = root;
	}
	if (ap != NULL) {
		ap->parent = root;
	}
	T = root;
	return OK;
}

/**
 * 用文件filename中的信息创建B-树，假设B-树中只有关键字信息。
 */
Status CreateBTree(BTree &T, char *filename)
{
	FILE *pf;
	KeyType e;
	pf = fopen(filename, "r");
	if (NULL == pf) {
		printf("打开文件%s失败！", filename);
		return ERROR;
	}
	while (EOF != fscanf(pf, "%d", &e)) {
		InsertBTree(T, e);
	}
	fclose(pf);
	return OK;
}

/**
 * 打印B-树，按先序顺序
 */
Status DisplayBTree(BTree T)
{
	int i;
	
	if (T != NULL) {
		for (i = 0; i <= T->keynum; i++) {
			if (i < T->keynum) {
				DisplayBTree(T->ptr[i]);
				printf("%d ", T->Key[i+1]);
			} else {
				DisplayBTree(T->ptr[i]);
			}
		}
	}
	return OK;
}

/**
 * 算法9.15，在非空双链树T中查找关键字等于K的记录，若存在，则返回查找过程中指向最后一个
 * 结点的指针，否则返回空指针。
 */
DLTree SearchDLTree(DLTree T, KeysType K)
{
	DLTree p, q; 
	int i = 0;
	bool finished = false;
	p = T->first;
	while (p != NULL && i < K.num) {
		while (p != NULL && p->symbol != K.ch[i]) {	
			//查找关键字第i位
			p = p->next;
		}
		if (p != NULL && i < K.num - 1) {	//准备查找下一位
			p = p->first;
		}
		++i;
	}
	if (p != NULL) {	//判断要查找的关键字是否是已有关键字的真子集
		q = p->first;
		while (q->kind != LEAF) {
			q = q->next;
		}
		if (q != NULL) {
			finished = true;
		}
	}
	if (finished) {		//要查找的关键字不是已有关键字的真子集
		return p;
	} else {
		return NULL;
	}
}