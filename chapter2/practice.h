#ifndef _PRACTICE_H_
#define _PRACTICE_H_

/* 习题2.38 结点类型 */
typedef struct myLNode{
	ElemType data;
	struct myLNode * prior;
	struct myLNode * next;
	int freq;   // 访问频度
}*myLink;

typedef struct {
	myLink head, tail;
	int len;
} myLinkList;

int compareList(struct Sqlist La, struct Sqlist Lb);
void invertList(struct LNode * &L);
void invertMergeList(struct LNode * &La, struct LNode * &Lb, struct LNode * &Lc);
Status initMyList(myLinkList &L);
void locate(myLinkList L, ElemType x);
#endif