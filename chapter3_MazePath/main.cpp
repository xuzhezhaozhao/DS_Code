#include <stdio.h>
#include <stdlib.h>

#include "my_headers.h"

int Map[SIZE][SIZE] = { {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 
			{1, 0, 0, 1, 0, 0, 0, 1, 0, 1}, 
			{1, 0, 0, 1, 0, 0, 0, 1, 0, 1}, 
			{1, 0, 0, 0, 0, 1, 1, 0, 0, 1}, 
			{1, 0, 1, 1, 1, 0, 0, 0, 0, 1}, 
			{1, 0, 0, 0, 1, 0, 0, 0, 0, 1}, 
			{1, 0, 1, 0, 0, 0, 1, 0, 0, 1}, 
			{1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
			{1, 1, 0, 0, 0, 0, 0, 0, 0, 1}, 
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};   // ÃÔ¹¬µØÍ¼
SqStack S;		// Â·¾¶Õ»

int main()
{
	InitStack(S);
	PosType start;
	PosType end;
	start.row = 1;
	start.col = 1;

	end.row = 8;
	end.col = 8;

	MazePath(start, end);
	StackTraverse(S, display_path);
	return 0;
}