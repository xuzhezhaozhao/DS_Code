/* 链队列的基本操作实现 */

#include <stdio.h>
#include <stdlib.h>

#include "my_headers.h"

/**
 * 构造一个空队列Q
 */
Status InitQueue (LinkQueue &Q)
{
	Q.front = (QNode *) malloc (sizeof(QNode));
	if (!Q.front) 
		return ERROR;
	Q.front->next = NULL;
	Q.rear = Q.front;
	return OK;
}

/**
 *  销毁队列
 */
Status DestroyQueue(LinkQueue &Q)
{
	while (Q.front) {
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
	return OK;
}

/**
 * 将Q清空, 并释放结点空间
 */
Status ClearQueue(LinkQueue &Q)
{
	QueuePtr p, temp;
	p = Q.front->next;
	Q.front->next = NULL;
	Q.rear = Q.front;
	while (p) {
		temp = p->next;
		free(p);
		p = temp;
	}
	return OK;
}

/**
 * 判断Q是否为空, 是返回TRUE，否则返回FALSE
 */
Status QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear)
		return TRUE;
	else
		return FALSE;
}

/**
 * 返回Q元素个数
 */
int QueueLength(LinkQueue Q)
{
	QueuePtr p;
	int len = 0;
	p = Q.front->next;
	while (p) {
		len++;
		p = p->next;
	}
	return len;
}

/**
 * 若队列不空，用e返回Q的队头元素，并返回OK，否则返回ERROR
 */
Status GetHead(LinkQueue Q, QElemType &e)
{
	if (Q.front == Q.rear)
		return ERROR;
	e = Q.front->next->data;
	return OK;
}

/**
 * 插入元素e为Q的新的队尾元素
 */
Status EnQueue(LinkQueue &Q, QElemType e)
{
	QueuePtr p;
	p = (QNode *) malloc (sizeof(QNode));   //生成新的结点
	if (!p)
		return ERROR;
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}

/**
 * 若队列不空，删除队列Q的队头元素，用e返回其值，返回OK，否则返回ERROR
 */
Status DeQueue(LinkQueue &Q, QElemType &e)
{
	QueuePtr p;
	p = Q.front->next;
	if (Q.front == Q.rear)
		return ERROR;
	e = p->data;
	if (Q.front->next == Q.rear)	//队列中只有一个元素时，还要修改尾指针
		Q.rear = Q.front;
	Q.front->next = p->next;
	free(p);
	p = NULL;
	return OK;
}

/**
 * 从队头到队尾遍历Q中每个元素调用visit(), visit()失败则操作失败
 */
Status QueueTraverse(LinkQueue Q, Status (*visit)(QElemType &e))
{
	QueuePtr p;
	p = Q.front->next;
	while (p) {
		if (!(*visit)(p->data))
			return ERROR;
		p = p->next;
	}
	return OK;
}

/**
 * 打印元素
 */
Status visit_display(QElemType &e)
{
	printf("%d ", e);
	return OK;
}