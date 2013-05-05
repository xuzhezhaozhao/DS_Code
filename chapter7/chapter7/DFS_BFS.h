#ifndef	_DFS_BFS_H_
#define _DFS_BFS_H_

typedef struct {		//Prim算法的辅助结构
	VertexType adjvex;
	VRType lowcost;
}lowedge[MAX_VERTEX_NUM];

typedef bool PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];	//Dijkstra算法辅助结构
typedef int ShortPathTable[MAX_VERTEX_NUM];			//同上
typedef int DistanceMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];	//Floyd算法辅助结构

void DFSTraverse(ALGraph G, Boolean visited[], Status (*Visit)(ALGraph G, int v));
void DFS(ALGraph G, int v, Boolean visited[], Status (*Visit)(ALGraph G, int v));
Status display(ALGraph G, int v);
void BFSTraverse(ALGraph G, Boolean visited[], Status (*Visit)(ALGraph G, int v));
Status DFSForst (ALGraph G, CSTree &T, bool visited[]);
Status DFSTree(ALGraph G, int v, CSTree T, bool visited[]);
void MiniSpanTree_PRIM(MGraph G, VertexType u);
int minimum(lowedge closedge, int len);
Status TopologicalSort(ALGraph G);
void FindInDegree(ALGraph G, int indegree[]);
Status TopologicalSort(ALGraph G, SqStack &T, int ve[]);
Status CriticalPath(ALGraph G, SqStack &T, int ve[]);
void ShortestPath_DIJ(MGraph G, int v0, PathMatrix &P, ShortPathTable &D);
void CopyPath(PathMatrix &P, int w, int v);
void DisplayShorstPath_DIJ(MGraph G, int v0, PathMatrix P, ShortPathTable D);
void ShortestPath_FLOYD(MGraph G, PathMatrix P[], DistanceMatrix D);
void DisplayShorstPath_FLOYD(MGraph G, PathMatrix P[], DistanceMatrix D);
#endif