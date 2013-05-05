#ifndef _TREE_H_
#define _TREE_H_

typedef int TElemType;		//定义二叉树结点的数据元素类型
typedef struct BiTNode {	//定义二叉树的结点
	TElemType data;
	struct BiTNode *lchild, *rchild;	//左右孩子指针
}BiTNode, *BiTree;

typedef BiTree SElemType;
typedef BiTree QElemType;

Status CreateBiTree(BiTree &T);
Status display(TElemType e);
Status PreOrderTraverse(BiTree T, Status (*visit)(TElemType e));
Status InOrderTraverse(BiTree T, Status (*visit)(TElemType e));
Status PostOrderTraverse(BiTree T, Status (*visit)(TElemType e));
Status LevelOrderTraverse(BiTree T, Status (*visit)(TElemType e));
Status PreOrderTraverse2(BiTree T, Status (*visit)(TElemType e));
Status InOrderTraverse2(BiTree T, Status (*visit)(TElemType e));
Status InOrderTraverse3(BiTree T, Status (*visit)(TElemType e));
Status PostOrderTraverse2(BiTree T, Status (*visit)(TElemType e));

#endif