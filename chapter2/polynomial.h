#ifndef	_POLYNOMIAL_H_
#define _POLYNOMIAL_H_

typedef struct {  //项的表示，数据类型
	float coef; // 系数
	int expn;   // 指数
} Term;

typedef struct PNode{    // 结点类型，单项
	Term elem;
	struct PNode * next;
}*pLink;

typedef struct {     //链表类型, 多项式表示
	pLink head, tail;
	int len;
}polynomial;
void CreatePolyn(polynomial &P, int m);
void DestroyPolyn(polynomial &P);
int PolyLength(polynomial &P);
void AddPolyn(polynomial &Pa, polynomial &Pb);
void subtractPolyn(polynomial &Pa, polynomial &Pb);
void MultiplyPolyn(polynomial &Pa, polynomial &Pb);

#endif