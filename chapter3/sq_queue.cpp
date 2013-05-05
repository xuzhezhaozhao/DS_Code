/* 循环队列的基本操作袖 */

#include <stdio.h>
#include <stdlib.h>

#include "my_headers.h"

/**
 * 初始化, 构造一个空的循环队列
 */
Status InitQueue(SqQueue &Q)
{
	Q.base = (QElemType *) malloc (MAXQSIZE*sizeof(QElemType));
	if (!Q.base)
		return ERROR;
	Q.front = 0;
	Q.rear = 0;
	return OK;
}

/**
 * 销毁队列
 */
Status DestroyQueue(SqQueue &Q)
{
	free(Q.base);
	Q.base = NULL;
	return OK;
}

/**
 * 清空队列
 */
Status ClearQueue(SqQueue &Q)
{
	Q.front = Q.rear = 0;
	return OK;
}

/**
 * 判断是否为空
 */
Status QueueEmpty(SqQueue &Q)
{
	if (Q.rear == Q.front)
		return TRUE;
	return FALSE;
}

/**
 * 返回队列Q元素个数
 */
Status QueueLength(SqQueue Q)
{
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;  // 参照的书目的算法，这个方法很妙
}

/**
 * 得到队头元素，用e返回, 队列为空返回ERROR，否则返回OK
 */
Status GetHead(SqQueue Q, QElemType &e)
{
	if (Q.rear == Q.front)
		return ERROR;
	e = *(Q.base+Q.front);
	return OK;
}

/**
 * 插入元素e为Q的新的队尾元素，队列已满返回ERROR，否则返回OK
 */
Status EnQueue(SqQueue &Q, QElemType e)
{
	if ((Q.rear+1)%MAXQSIZE == Q.front)   //队列满, 使用求余使算法更简便
		return ERROR;
	*(Q.base+Q.rear) = e;
	Q.rear = (Q.rear+1)%MAXQSIZE; 
	return OK;
}

/**
 * 若队列不空，返回OK，否则返回ERROR，删除队头元素，用e返回其值，
 */
Status DeQueue(SqQueue &Q, QElemType &e)
{
	if (Q.front == Q.rear)
		return ERROR;
	e = *(Q.base+Q.front);
	Q.front = (Q.front+1)%MAXQSIZE;
}

/**
 * 从队头到队尾遍历Q中每个元素调用visit(), visit()失败则操作失败
 */
Status QueueTraverse(SqQueue Q, Status (*visit)(QElemType &e))
{
	int p;
	p = Q.front;
	while (p != Q.rear) {
		if (!(*visit)(*(Q.base+p)))
			return ERROR;
		p = (p+1)%MAXQSIZE;
	}
	return OK;
}