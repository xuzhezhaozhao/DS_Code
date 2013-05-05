#ifndef _PRACTICE_H_
#define _PRACTICE_H_

enum Mark {Left, Right, Visit};	//向左、向右、访问结点的标志
typedef struct PTagNode {	//习题6.39的数据结构
	TElemType data;
	Mark mark;
	struct PTagNode *lchild, *rchild, *parent;
}PTagNode, *PTagTree;

Status CreatePTagTree(PTagTree &T);
Status MyPostOrderTraverse(PTagTree T, Status (*visit)(TElemType e));
Status get_PreOrderValue(BiTree T, int k, int &count, int &value);
Status get_InOrderValue(BiTree T, int k, int &count, int &value);
Status get_PostOrderValue(BiTree T, int k, int &count, int &value);
void get_LeafCount(BiTree T, int &count);
void ExchangSubtree(BiTree T);
Status get_NodeDeepth(BiTree T, TElemType x, int &deep);
int get_TreeDeepth(BiTree T);
void DestroyTree(BiTree &T);
void DeleteNode(BiTree &T, TElemType x);
void CopyTree(BiTree T, BiTree &Tc);
Status PathTree(BiTree &T, BiTree p);
Status get_MinComAncester(BiTree root, BiTree p, BiTree q, BiTree m);
bool isCompleteBiTree(BiTree T);
Status MyCreateTree(BiTree &T);
Status SearchNode(BiTree R[], int len, char c, BiTree &p);
char PrecedeTree(char c1, char c2);
void OutputExpression(BiTree T);
bool isOpt(char c);

#endif