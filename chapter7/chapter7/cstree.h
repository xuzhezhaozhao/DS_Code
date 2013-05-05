#ifndef _CSTREE_H_
#define _CSTREE_H_

typedef VertexType CSElemType;
typedef struct CSNode {
	CSElemType data;
	struct CSNode *lchild, *nextsibling;
}CSNode, *CSTree;

#endif
