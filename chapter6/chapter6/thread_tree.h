/* 线索二叉树 */

#ifndef _THREAD_TREE_H_
#define _THREAD_TREE_H_

typedef enum PointerTag {Link, Thread};	// Link == 0, 指针; Thread == 1, 线索
typedef struct BiThrNode {
	TElemType data;
	struct BiThrNode *lchild, *rchild;
	PointerTag LTag, RTag;
}BiThrNode, *BiThrTree;

Status CreateBiThrTree(BiThrTree &T);
Status InOrderTraverse_Thr(BiThrTree T, Status (*visit)(TElemType e));
Status InOrderThreading(BiThrTree &Thrt, BiThrTree T);
void InThreading(BiThrTree p);

#endif