#include <stdio.h>
#include <stdlib.h>

#include "my_headers.h"

extern int chess[8][8];
extern int count;

int main()
{
	BiTree T;
	CreateBiTree(T);
	//CopyTree(T, Tc);
	//PreOrderTraverse(T, display);

	//int value;
	//int count = 0;
	//int k = 3;
	//if (OK == get_PostOrderValue(T, k, count, value))
	//	printf("\n后序序列中的第%d个元素为：%c\n", k, value);
	//else
	//	printf("\nERROR\n");
	//get_LeafCount(T, count);
	//printf("\n叶子数目：%d\n", count);

	//ExchangSubtree(T);
	//printf("\n---------------------------------\n");
	//PreOrderTraverse(T, display);
	//TElemType x = 'd';
	//int deep;
	//if (OK == get_NodeDeepth(T, x, deep))
	//	printf("\n%d\n", deep);
	//else
	//	printf("\nERROR\n");
	//DeleteNode(T, x);
	//printf("\n---------------------------------\n");
	//PreOrderTraverse(T, display);
	//LevelOrderTraverse(T, display);
	//printf("\n---------------------------------\n");
	//LevelOrderTraverse(Tc, display);
	//p = T->lchild->rchild;
	//PathTree(T, p);
	//printf("\n---------------------------------\n");
	//LevelOrderTraverse(T, display);

	//if (isCompleteBiTree(T))
	//	printf("OK!\n");
	//else
	//	printf("ERROR!\n");

	// if (OK == MyCreateTree(T)) {
	//	PreOrderTraverse(T, display);
	//	printf("\n---------------------------------\n");
	//	LevelOrderTraverse(T, display);
	//}
	OutputExpression(T);
	return 0;
}