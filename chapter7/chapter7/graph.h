#ifndef	_GRAPH_H_
#define	_GRAPH_H_

#define MAX_VERTEX_NUM 20			//图最大顶点个数
typedef enum {DG, DN, UDG, UDN} GraphKind;	//有向图，有向网，无向图，无向网
typedef char InfoType;				//弧相关信息的指针
typedef char VertexType;			//顶点类型

/* 图的数组(邻接矩阵)存储表示 */
#define INFINITY INT_MAX			//最大值
typedef int VRType;				//顶点关系类型，对无权图，用0，1表示相邻否，对带权图，表示权值类型
typedef struct ArcCell {
	VRType	adj;				//权值
	InfoType *info;		
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct {
	VertexType vexs[MAX_VERTEX_NUM];	//顶点向量
	AdjMatrix arcs;				//邻接矩阵
	int vexnum, arcnum;			//图的当前顶点数和弧数
	GraphKind kind;				//图的种类标志
}MGraph;

/* 图的邻接表(Adjacency List)存储表示 */
typedef struct ArcNode {
	int adjvex;				//该弧所指向的顶点的位置
	struct ArcNode *nextarc;		//指向下一条弧的指针
	InfoType *info;				//该弧相关信息的指针
}ArcNode;
typedef struct VNode {				//头结点
	VertexType data;			//顶点信息
	ArcNode *firstarc;			//指向依附该顶点的第一条弧的指针
}VNode, AdjList[MAX_VERTEX_NUM];
typedef struct {
	AdjList vertices;			//存放头结点的数组
	int vexnum, arcnum;			//图的顶点数和弧数
	GraphKind kind;				//图的种类
}ALGraph;

/* 有向图的十字链表(Orthogonal List)表示 */
typedef struct ArcBox {
	int tailvex, headvex;			//该弧的尾和头顶点的位置
	struct ArcBox *hlink, *tlink;		//分别为弧头相同和弧尾相同的弧的链域
	InfoType *info;				//该弧的相关信息指针
}ArcBox;
typedef struct VexNode {			//头结点
	VertexType data;			//顶点信息
	ArcBox *firstin, *firstout;		//分别指向该顶点的第一条入弧和出弧
}VexNode;
typedef struct {
	VexNode xlist[MAX_VERTEX_NUM];		//表头向量
	int vexnum, arcnum;			//有向图的顶点数和弧数
}OLGraph;

/* 无向图的邻接多重表存储表示形式 */
typedef enum {unvisited, visited} VisitIf;
typedef struct EBox {
	VisitIf mark;				//访问标记
	int ivex, jvex;				//该边依附的两个顶点的位置
	struct EBox *ilink, *jlink;		//分别指向依附这两个顶点的下一条边
	InfoType *info;				//该边信息指针
}EBox;
typedef struct VexBox {
	VertexType data;
	EBox *firstedge;			//指向第一条依附该顶点的边
}VexBox;
typedef struct {
	VexBox adjmulist[MAX_VERTEX_NUM];	//无向图顶点向量
	int vexnum, edgenum;			//无向图的当前顶点数和边数
}AMLGraph;

/* 函数声明 */
Status CreateUDN(MGraph &G);
Status CreateDN(MGraph &G);
int LocateVex(MGraph G, VertexType u);
int LocateVex(OLGraph G, VertexType u);
void Input(InfoType * &info);
Status CreateDG(OLGraph &G);
Status CreateDN(ALGraph &G);
Status CreateUDG(ALGraph &G);
Status CreateDG(ALGraph &G);
int FirstAdjVex(ALGraph G, int v);
int NextAdjVex(ALGraph G, int v, int w);
VertexType GetVex(ALGraph G, int v);
#endif