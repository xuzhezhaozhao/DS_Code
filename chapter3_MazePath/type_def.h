/* 宏定义及类型定义 */

#ifndef _TYPE_DEF_H_
#define _TYPE_DEF_H_

#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
#define STACK_INIT_SIZE 100     //栈初始化值
#define STACKINCREMENT 10       //栈容量每次增加的值
#define SIZE 10			//定义迷宫地图大小

typedef struct {
	int row;    // 行，0起始
	int col;    // 列，0起始
}PosType;
typedef struct {
	int ord;	// 通道块在路径上的序号
	PosType seat;   // 通道块在迷宫中的坐标位置
	int di;		//从此通道走向下一通道块的方向
}SElemType;

typedef int Status;

#endif