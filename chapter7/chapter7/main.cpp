#include <stdio.h>
#include <stdlib.h>

//#define NDEBUG
#include <assert.h>

#include "my_headers.h"
#define MAX 100

int main()
{
	MGraph G;
	PathMatrix P[MAX_VERTEX_NUM];
	DistanceMatrix D;
	CreateDN(G);
	ShortestPath_FLOYD(G, P, D);
	DisplayShorstPath_FLOYD(G, P, D);

	return 0;
}