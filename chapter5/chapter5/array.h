#ifndef _ARRAY_H_
#define _ARRAY_H_

#define MAX_ARRAY_DIM 8		//假设数组维数的最大值为8
typedef struct {
	ElemType *base;		//数组元素基址，由InitArray分配
	int dim;		//数组维数
	int *bounds;		//数组维界基址，由InitArray分配
	int *constants;		//数组映像函数常量基址，由InitArray分配
}Array;

Status InitArray(Array &A, int dim, ...);
Status DestroyArray(Array &A);
Status Locate(Array A, va_list ap, int &off);
Status Value(Array A, ElemType &e, ...);
Status Assign(Array &A, ElemType e, ...);

#endif