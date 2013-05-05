/* 循环队列，队列的顺序表示和实现 */

#ifndef _SQ_QUEUE_H_
#define _SQ_QUEUE_H_

#define MAXQSIZE 5

typedef struct {		//定义循环队列
	QElemType *base;	//初始化的动态分配存储空间
	int front;		//头指针
	int rear;		//尾指针
}SqQueue;

Status InitQueue(SqQueue &Q);
Status DestroyQueue(SqQueue &Q);
Status ClearQueue(SqQueue &Q);
Status QueueEmpty(SqQueue &Q);
Status QueueLength(SqQueue Q);
Status GetHead(SqQueue Q, QElemType &e);
Status EnQueue(SqQueue &Q, QElemType e);
Status DeQueue(SqQueue &Q, QElemType &e);
Status QueueTraverse(SqQueue Q, Status (*visit)(QElemType &e));




#endif