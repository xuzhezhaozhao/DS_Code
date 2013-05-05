/* 树的双亲表示法，P135*/

#ifndef _PTREE_H_
#define _PTREE_H_

#define MAX_TREE_SIZE 100
typedef struct PTNode {	//结点结构
	TElemType data;
	int parent;	//双亲位置
}PTNode;
typedef struct {	//树结构
	PTNode nodes[MAX_TREE_SIZE];	
	int r, n;	//根的位置和结点数
}PTree;

#endif