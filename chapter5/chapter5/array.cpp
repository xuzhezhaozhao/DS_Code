#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "my_headers.h"

/**
 * 初始化数组
 */
Status InitArray(Array &A, int dim, ...)
{
	va_list ap;
	int i;
	int elemtotal = 1;	//保存数组的元素个数
	if (dim < 1 || dim > MAX_ARRAY_DIM)
		return ERROR;
	A.dim = dim;
	A.bounds = (int *)malloc(dim*sizeof(int));
	if (!A.bounds)
		return ERROR;
	va_start(ap, dim);
	for (i=0; i<dim; i++) {
		A.bounds[i] = va_arg(ap, int);	//读入一个变长参数
		if (A.bounds[i] < 0)
			return ERROR;
		elemtotal *= A.bounds[0];
	}

	va_end(ap);
	A.base = (ElemType *)malloc(elemtotal*sizeof(ElemType));
	if (!A.base)
		return ERROR;
	//下面求映像函数ci,并存入A.constants[i-1], i=1,...,dim
	A.constants = (int *)malloc(dim*sizeof(int));
	if (!A.constants)
		return ERROR;
	A.constants[dim-1] = 1;	//L=1，指针的增减以元素的大小为单位
	for (i=dim-2; i>=0; i--)
		A.constants[i] = A.bounds[i+1] * A.constants[i+1];

	return OK;
}

/**
 * 销毁数组A
 */
Status DestroyArray(Array &A)
{
	if (!A.base)
		return ERROR;
	free(A.base);
	A.base = NULL;
	if (!A.bounds)
		return ERROR;
	free(A.bounds);
	A.bounds = NULL;
	if (!A.constants)
		return ERROR;
	free(A.constants);
	A.constants = NULL;

	return OK;
}

/**
 * 若ap指示的各下标值合法，则求出该元素在A中的相对地址off
 */
Status Locate(Array A, va_list ap, int &off)
{
	int i, ind;
	off = 0;
	for (i=0; i<A.dim; i++) {
		ind = va_arg(ap, int);
		if (ind <0 || ind >= A.bounds[i])
			return ERROR;
		off += A.constants[i] * ind;
	}

	return OK;
}

/**
 * A是n维数组，e为元素变量，随后是n个下标值，若下标不越界，没e赋值为所指定的A的元素值，并返回OK
 */
Status Value(Array A, ElemType &e, ...)
{
	int result;
	int off;
	va_list ap;
	va_start(ap, e);
	result = Locate(A, ap, off);
	if (ERROR == result)
		return ERROR;
	e = *(A.base+off);
	return OK;
}

/**
 * 将e值赋给所指定的A的元素，并返回OK
 */
Status Assign(Array &A, ElemType e, ...)
{
	int result, off;
	va_list ap;
	va_start(ap, e);
	result = Locate(A, ap, off);
	if (ERROR == result)
		return ERROR;
	*(A.base+off) = e;
	return OK;
}