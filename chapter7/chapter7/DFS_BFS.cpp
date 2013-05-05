#include <stdio.h>
#include <stdlib.h>

#include "my_headers.h"

/**
 * 算法7.4，对图G作深度优先遍历, 数组visited为访问标志数组，Visit为访问函数
 */
void DFSTraverse(ALGraph G, Boolean visited[], Status (*Visit)(ALGraph G, int v))
{
	int v;
	for (v = 0; v < G.vexnum; v++) {	//初始化标志数组
		visited[v] = false;
	}
	for (v = 0; v < G.vexnum; v++) {
		if (!visited[v])		//对尚未访问过的结点调用DFS
			DFS(G, v, visited, Visit);
	}
}

/**
 * 算法7.5，从第v个顶点出发递归地深度优先遍历图G, visited为结点访问标志数组，Visit为访问函数
 */
void DFS(ALGraph G, int v, Boolean visited[], Status (*Visit)(ALGraph G, int v))
{
	int w;
	visited[v] = true;
	Visit(G, v);		//访问第v个结点
	for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)) {
		if (!visited[w])
			DFS(G, w, visited, Visit);
	}
}

/**
 * 打印图G中第v个顶点的信息 
 */
Status display(ALGraph G, int v)
{
	printf("%c ", G.vertices[v].data);
	return OK;
}

/**
 * 算法7.6，按广度优先非递归遍历图G，使用辅助队列Q和访问标志数组visited
 */
void BFSTraverse(ALGraph G, Boolean visited[], Status (*Visit)(ALGraph G, int v))
{
	int u, v, w;
	LinkQueue Q;
	InitQueue(Q);
	
	for (v = 0; v < G.vexnum; v++) {
		visited[v] = false;
	}

	for (v = 0; v < G.vexnum; v++) {
		if (!visited[v]) {
			visited[v] = true;
			Visit(G, v);
			EnQueue(Q, v);
			while (!QueueEmpty(Q)) {
				DeQueue(Q, u);		//附着元素出列并置为u
				for (w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w)) {
					if (!visited[w]) {
						visited[w] = true;
						Visit(G, w);
						EnQueue(Q, w);
					}
				}
			}
		}
	}
}

/**
 * 算法7.7，建立无向图G的深度优先生成森林的孩子兄弟链表
 */
Status DFSForst(ALGraph G, CSTree &T, bool visited[])
{
	int v;
	CSTree p, q;
	T = NULL;
	for (v = 0; v < G.vexnum; v++) {
		visited[v] = false;
	}
	for (v=0; v < G.vexnum; v++) {
		if (!visited[v]) {
			p = (CSTree) malloc (sizeof(CSNode));
			if (!p)
				return ERROR;
			p->data = GetVex(G, v);
			p->lchild = NULL;
			p->nextsibling = NULL;
			if (!T) {	//是第一棵生成树的根
				T = p;
			} else {
				q->nextsibling = p;
			}
			q = p;
			DFSTree(G, v, p, visited);
		}
	}
	return OK;
}

/**
 * 算法7.8，从第v个顶点出发深度优先遍历图G，建立以T为根的生成树
 */
Status DFSTree(ALGraph G, int v, CSTree T, bool visited[])
{
	bool first;
	CSTree p, q;
	int w;
	visited[v] = true;
	first = true;
	for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)) {
		if (!visited[w]) {
			p = (CSTree) malloc (sizeof(CSNode));		//分配孩子结点
			if (!p) {
				return ERROR;
			}
			p->data = GetVex(G, w);
			p->lchild = NULL;
			p->nextsibling = NULL;
			if (first) {
				T->lchild = p;
				first = false;
			} else {
				q->nextsibling = p;
			}
			q = p;
			DFSTree(G, w, q, visited);
		}
	}
	return OK;
}

/**
 * 算法7.9，Prim算法，最小生成树
 */
void MiniSpanTree_PRIM(MGraph G, VertexType u)
{
	int i, j, k;
	lowedge closedge;
	k = LocateVex(G, u);
	for (j = 0; j < G.vexnum; j++) {	//辅助数组初始化
		if (j != k) {
			closedge[j].adjvex = u;
			closedge[j].lowcost = G.arcs[k][j].adj;
		}
	}
	closedge[k].lowcost = 0;
	printf("最优树的边：\n");
	for (i = 1; i < G.vexnum; i++) {	//选择其余G.vexnum-1个顶点
		k = minimum(closedge, G.vexnum);		//求出T的下一个结点
		printf("%c %c\n", closedge[k].adjvex, G.vexs[k]);
		closedge[k].lowcost = 0;	//第k顶点并入U集
		for (j = 0; j < G.vexnum; j++) {
			if (G.arcs[k][j].adj < closedge[j].lowcost) {	//新顶点并入U后重新选择最小边
				closedge[j].adjvex = G.vexs[k];
				closedge[j].lowcost = G.arcs[k][j].adj;
			}
		}
	}
}

/**
 * 求closedge中权值非0的最小的顶点
 */
int minimum(lowedge closedge, int len)
{
	int min, i, j;
	min = -1;
	for (i = 0; i < len; i++) {
		if (closedge[i].lowcost != 0) {
			min = i;
			break;
		}
	}

	for (j = i; j < len; j++) {
		if (closedge[j].lowcost != 0 && closedge[min].lowcost > closedge[j].lowcost) {
			min = j;
		}
	}
	return min;
}

/**
 * 算法7.12，求拓补序列，有向图G用邻接表存储结构，若G中无回路则输出拓补序列并返回OK，否则返回ERROR
 */
Status TopologicalSort(ALGraph G)
{
	int i, j, count;
	ArcNode *p;
	int indegree[MAX_VERTEX_NUM];
	int stack[MAX_VERTEX_NUM];		// 模拟栈的功能
	int top = 0;				// 栈指针

	FindInDegree(G, indegree);
	for (i = 0; i < G.vexnum; i++) {
		if (0 == indegree[i]) {		//初始时所有入度为0的顶点入栈
			stack[top] = i;
			++top;
		}
	}
	count = 0;				//拓补序列内顶点数计数
	while (0 != top) {
		--top;
		i = stack[top];			//弹栈访问入度为0的顶点
		printf("%d: %c\n", count+1, G.vertices[i].data);	//输出顶点信息
		++count;			//计数加1
		for (p = G.vertices[i].firstarc; p != NULL; p = p->nextarc) {
			j = p->adjvex;		//顶点的入度减1
			--indegree[j];
			if (0 == indegree[j]) {
				stack[top] = j;		//入度为0顶点进栈
				++top;
			}
		}
	}

	if (count < G.vexnum) {				//说明有向图中存在回路
		return ERROR;
	} else {
		return OK;
	}
}

/**
 * 求邻接表表示的有向图G的各顶点的入度，indegree数组中保存各顶点的入度
 */
void FindInDegree(ALGraph G, int indegree[])
{
	int i, j;
	ArcNode *p;
	for (i = 0; i < G.vexnum; i++) {		//初始化入度数组
		indegree[i] = 0;
	}
	for (i = 0; i < G.vexnum; i++) {
		for (p = G.vertices[i].firstarc; p != NULL; p = p->nextarc) {
			j = p->adjvex;
			++indegree[j];
		}
	}
}

/**
 * 算法7.13，有向网G采用邻接表存储，求各顶点事件的最早发生时间ve
 * T为拓补序列顶点栈
 * 若G无回路，则用栈T返回G的一个拓补序列，且函数值为OK，否则为ERROR
 */
Status TopologicalSort(ALGraph G, SqStack &T, int ve[])
{
	SqStack S;		// S为零入度栈
	int indegree[MAX_VERTEX_NUM];
	int count, i, j, k;
	int arcvalue = 0;
	ArcNode *p;
	InitStack(S);
	InitStack(T);
	FindInDegree(G, indegree);
	for (i = 0; i < G.vexnum; i++) {
		if (0 == indegree[i]) {		//初始时所有入度为0的顶点入栈，此时应只有源点入栈
			Push(S, i);
		}
	}
	count = 0;
	for (i = 0; i < G.vexnum; i++) {
		ve[i] = 0;
	}
	while (!StackEmpty(S)) {
		Pop(S, j);
		Push(T, j);
		++count;
		for (p = G.vertices[j].firstarc; p != NULL; p = p->nextarc) {
			k = p->adjvex;
			--indegree[k];
			if (0 == indegree[k]) {
				Push(S, k);
			}
			arcvalue = atoi(p->info);		//活动时间, 将字符转成整数
			if (ve[j] + arcvalue > ve[k]) {		//选择最大的，这一步最关键，参看书本P184
				ve[k] = ve[j] + arcvalue;
			}
		}
	}

	if (count < G.vexnum) {
		return ERROR;
	} else {
		return OK;
	}
}

/**
 * 算法7.14，G为有向网，输出G的各项关键活动
 * 栈T中保存图G的拓补序列，ve数组中为各顶点的最早开始时间
 */
Status CriticalPath(ALGraph G, SqStack &T, int ve[])
{
	int i, j, k, dut, ee ,el;
	ArcNode *p;
	int vl[MAX_VERTEX_NUM];
	if (ERROR == TopologicalSort(G, T, ve)) {
		return ERROR;
	}
	for (i = 0; i < G.vexnum; i++) {		//初始化顶点的最迟发生时间
		vl[i] = ve[G.vexnum-1];
	}
	while (!StackEmpty(T)) {			//按拓补逆序求各顶点的最晚开始时间vl值
		Pop(T, j);
		for (p = G.vertices[j].firstarc; p != NULL; p = p->nextarc) {
			k = p->adjvex;
			dut = atoi(p->info);		//活动时间
			if (vl[k] - dut < vl[j]) {
				vl[j] = vl[k] - dut;
			}
		}
	}

	printf("关键活动：");
	for (j = 0; j < G.vexnum; j++) {	//求活动的最早开始时间和最晚开始时间，并求出关键活动
		for (p = G.vertices[j].firstarc; p != NULL; p = p->nextarc) {
			k = p->adjvex;
			dut = atoi(p->info);
			ee = ve[j];		//活动的最早开始时间
			el = vl[k]-dut;		//活动的最晚开始时间
			if (ee == el) {		//关键活动
				printf("%c%c ", G.vertices[j].data, G.vertices[k].data);
			}
		}
	}
	printf("\n");
}

/**
 * 算法7.15，最短路径算法，Dijkstra算法
 * 返回有向网G的v0顶点到其余顶点v的最短路径P[v], 及其带权长度为D[v]
 */
void ShortestPath_DIJ(MGraph G, int v0, PathMatrix &P, ShortPathTable &D)
{
	bool final[MAX_VERTEX_NUM];	//final[v]为true表示已经求得从v0到v的最短路径
	bool flag = false;		//标志V－S中的顶点距离v0是否都为无限大
	int v, w, i, min;
	for (v = 0; v < G.vexnum; v++) {	//初始化初始状态
		final[v] = false;
		D[v] = G.arcs[v0][v].adj;
		for (w = 0; w < G.vexnum; w++) {
			P[v][w] = false;	//设空路径
		}
		if (D[v] < INFINITY) {		//表明该顶点与v0直接相连，将这两点加入点v的路径中
			P[v][v0] = true;
			P[v][v] = true;
		}
	}
	D[v0] = 0;
	final[v0] = true;			//初始化，v0顶点属于S集

	// 开始主循环，每次求得v0到某个顶点的最短路径，并加入v到S集
	for (i = 1; i < G.vexnum; i++) {
		flag = false;
		min = INFINITY;
		for (w = 0; w < G.vexnum; w++) {
			if (!final[w]) {	//w顶点在V－S中
				if (D[w] < min) {
					flag = true;
					v = w;
					min = D[w];
				}
			}
		}
		if (false == flag) {		//如果v0到V－S中的距离都是无限大，则退出循环，算法结束
			break;
		}
		final[v] = true;		//离v0顶点最近的顶点v加入S集中，执行的是算法的第2步
		for (w = 0; w < G.vexnum; w++) {	
			//更新当前最短路径及距离,更新新加入的点到V－S中其他点的D[k], 关键的一步
			if (!final[w] && INFINITY != G.arcs[v][w].adj && (min + G.arcs[v][w].adj) < D[w]) {
				D[w] = min + G.arcs[v][w].adj;
				CopyPath(P, w, v);
				P[w][w] = true;		//P[w] = P[w] + P[v];
			}
		}
	}
}

/**
 * 复制最短路径算法顶点v的路径到顶点w
 */
void CopyPath(PathMatrix &P, int w, int v)
{
	int i;
	for (i = 0; i < MAX_VERTEX_NUM; i++) {
		P[w][i] = P[v][i];
	}
}

/**
 * 打印Dijkstra求得的v0到其余各点的最短路径P[0...G.vexnum]及路径长度D[0...G.vexnum]
 */
void DisplayShorstPath_DIJ(MGraph G, int v0, PathMatrix P, ShortPathTable D)
{
	int i ,j;
	printf("从顶点%c出发到其余各顶点的最短路径如下：\n", G.vexs[v0]);
	for (i = 0; i < G.vexnum; i++) {
		if (i != v0) {
			if (INFINITY == D[i]) {
				printf("顶点%c不可到达！", G.vexs[i]);
			} else {
				printf("顶点%c(距离%d)：", G.vexs[i], D[i]);
				for (j = 0; j < G.vexnum; j++) {
					if (true == P[i][j]) {
						printf("%c ", G.vexs[j]);
					}
				}
			}
			printf("\n");
		}
	}
}

/**
 * 算法7.16, 用Floyd算法求有向网G中各对顶点v和w之间的最短路径P[v][w]及其带权长度D[v][w],
 * 若P[v][w][u]为true则u是从v到w当前求得最短路径上的顶点
 */
void ShortestPath_FLOYD(MGraph G, PathMatrix P[], DistanceMatrix D)
{
	int v, w, u, i;
	for (v = 0; v < G.vexnum; v++) {		//初始化各对结点之间初始已知路径及距离
		for (w = 0; w < G.vexnum; w++) {
			D[v][w] = G.arcs[v][w].adj;
			for (u = 0; u < G.vexnum; u++) {
				P[v][w][u] = false;
			}
			if (D[v][w] < INFINITY) {	//v到w有直接路径
				P[v][w][v] = true;
				P[v][w][w] = true;
			}
		}
	}

	for (u = 0; u < G.vexnum; u++) {					//u为v到w的中间路径上的顶点
		for (v = 0; v < G.vexnum; v++) {
			for (w = 0; w < G.vexnum; w++) {
				if (D[v][u] != INFINITY && D[u][w] != INFINITY 
					&& D[v][u] + D[u][w] < D[v][w]) {	//从v经u到w的一条路径更短
					D[v][w] = D[v][u] + D[u][w];
					for (i = 0; i < G.vexnum; i++) {	//更新路径
						P[v][w][i] = P[v][u][i] || P[u][w][i];
					}
				}
			}
		}
	}
}

/**
 * 打印FLOYD求得的有向图G中各对顶点之间的最短路径及带权长度
 */
void DisplayShorstPath_FLOYD(MGraph G, PathMatrix P[], DistanceMatrix D)
{
	int i, j, k;
	for (i = 0; i < G.vexnum; i++) {
		for (j = 0; j < G.vexnum; j++) {
			if (i != j) {
				if (INFINITY == D[i][j]) {
					printf("节点%c到%c不可到达！\n", G.vexs[i], G.vexs[j]);
				} else {
					printf("节点%c%c之间(最短距离%d)：", G.vexs[i], G.vexs[j], D[i][j]);
					for (k = 0; k < G.vexnum; k++) {
						if (true == P[i][j][k]) {
							printf("%c", G.vexs[k]);
						}
					}
					printf("\n");
				}
			}
		}
	}
}