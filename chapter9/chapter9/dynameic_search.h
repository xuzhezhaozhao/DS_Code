/* 动态查找表 */

#ifndef _DYNAMIC_SEARCH_H_
#define _DYNAMIC_SEARCH_H_

/* AVL平衡树 */
typedef BiTree BSTree;			//定义平衡二叉树
typedef BiTNode BSTNode;		//平衡二叉树结点
#define LH +1				//左高
#define EH 0				//等高
#define RH -1				//右高

/* B-树 */
#define m 3				// B-树的阶
#define RECORD_MAX_SIZE	100		//记录中字符的最大值
typedef char Record[RECORD_MAX_SIZE];

typedef struct BTNode {			//定义B-树的结点
	int keynum;			//结点中关键字的个数
	struct BTNode *parent;		//指向双亲结点
	KeyType Key[m + 1];		//关键字向量，0号单元未用
	struct BTNode *ptr[m + 1];	//子树指针向量，0号单元使用
	Record recptr[m + 1];		//记录指针向量，0号单元未用
}BTNode, *BTree;

typedef struct {
	BTNode *pt;			//指向找到的结点
	int i;				//1...m, 在结点中的关键字序号
	int tag;			//1：查找成功，0：查找失败
}Result;				//B-树的查找结果类型

/* 键树，双链树存储表示 */
#define MAXKEYLEN 16			//关键字最大长度
typedef struct {
	char ch[MAXKEYLEN];
	int num;			//关键字长度
}KeysType;				//关键字类型
typedef enum {LEAF, BRANCH} NodeKind;	//结点类型，{叶子，分支}
typedef struct DLTNode {
	char symbol;			//关键字字符
	struct DLTNode *next;		//指向下一个兄弟结点
	NodeKind kind;
	union {
		Record infoptr;		//叶子结点的记录指针
		struct DLTNode *first;	//分支结点的第一个孩子结点
	};
}DLTNode, *DLTree;

BiTNode* SearchBSTa(BiTree T, KeyType key, BiTree f, BiTree &pr);
bool SearchBSTb(BiTree T, KeyType key, BiTree f, BiTree &p);
bool InsertBST(BiTree &T, ElemType e);
bool DeleteNodeBST(BiTree &T, KeyType key);
Status DeleteNode(BiTree &T, BiTree &p, BiTree pr);
void R_Rotate(BSTree &p);
void L_Rotate(BSTree &p);
Status InsertAVL(BSTree &T, ElemType e, bool &taller);
void LeftBalance(BSTree &T);
void RightBalance(BSTree &T);
Result SearchBTree(BTree T, KeyType K);
int Search(BTree T, KeyType K);
Status InsertBTree(BTree &T, KeyType K);
Status Insert(BTree p, int i, KeyType x, BTree ap);
Status split(BTree p, int s, BTree &ap);
Status NewRoot(BTree &T, BTree q, int x, BTree ap);
Status CreateBTree(BTree &T, char *filename);
Status DisplayBTree(BTree T);
DLTree SearchDLTree(DLTree T, KeysType K);

#endif