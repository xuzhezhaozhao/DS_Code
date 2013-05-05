#ifndef _TYPE_H_
#define _TYPE_H_

#define OK 0
#define ERROR -1
#define FILE_NOT_EXIT -2	
#define TRUE 1
#define FALSE 0
#define STACK_INIT_SIZE 100		//栈初始化值
#define STACKINCREMENT 10		//栈容量每次增加的值
#define DATA_SIZE 20			//表中数据内容的大小

typedef int Status;
typedef int KeyType;

typedef struct {
	KeyType key;			//关键字
	char data[DATA_SIZE];		//数据内容
	float weigth;			//该数据被查找的频率的权值
}ElemType;

#define EQ(a, b) ((a) == (b))
#define LT(a, b) ((a) < (b))
#define LQ(a, b) ((a) <= (b))

#endif