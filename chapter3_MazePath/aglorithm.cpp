/* 书本上第三章算法实现 */
#include <stdio.h>
#include <stdlib.h>

#include "my_headers.h"

/**
 * 判断当前位置能不能通过，当前位置可通过是指该位置未曾到达过
 */
bool Pass(PosType curpos)
{
	if (1 == Map[curpos.row][curpos.col])
		return false;
	return true;
}

/**
 * 在走过的地方留下足迹
 */
void FootPrint(PosType curpos)
{
	Map[curpos.row][curpos.col] = 1;
}

/**
 * 下一个位置，di从1到4表示从东到北
 */
PosType NextPos(PosType pos, int di)
{
	PosType curpos;
	switch (di) {
	case 1:   //东, 列加1
		curpos.row = pos.row;
		curpos.col = pos.col+1;
		break;
	case 2:  //南，行加1
		curpos.row = pos.row+1;
		curpos.col = pos.col;
		break;
	case 3:  //西，列减1
		curpos.row = pos.row;
		curpos.col = pos.col-1;
		break;
	case 4:  //北，行减1
		curpos.row = pos.row-1;
		curpos.col = pos.col;
		break;
	}
	return curpos;
}

/**
 * 算法3.3，迷宫算法
 */
Status MazePath(PosType start, PosType end)
{
	PosType curpos;
	int curstep = 1; //探索第一步
	curpos = start;		
	SElemType e;		//通道块
	do {
		if (Pass(curpos)) {   // 如果当前位置能通过
			FootPrint(curpos);     //留下足迹
			e.ord = curstep;
			e.seat = curpos;
			e.di = 1;		
			Push (S, e);		// 加入路径
			if (curpos.row == end.row && curpos.col == end.col)
				return (OK);	//到达终点
			curpos = NextPos(curpos, 1);	//将当前位置的东邻设为下一位置
			curstep++;		//探索下一步
		}  else {    //如果当前位置不能通过
			if (!StackEmpty(S)) {
				Pop(S, e);   
				while (4 == e.di && !StackEmpty(S))
					Pop(S, e);	//即该位置的4方向都已经探索完成，就再退回一步
				if (e.di < 4) {    //换一个方向探索
					e.di++;
					Push(S, e);
					curpos = NextPos(e.seat, e.di);
				}
			}
		}
	}while(!StackEmpty(S));

	return ERROR;
}

Status display_path(SElemType e)
{
	printf("(%d, %d) ", e.seat.row, e.seat.col);
	switch (e.di) {
	case 1:
		printf("东\n");
		break;
	case 2:
		printf("南\n");
		break;
	case 3:
		printf("西\n");
		break;
	case 4:
		printf("北\n");
		break;
	}
	return OK;
}