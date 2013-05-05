#ifndef _SELECT_SORT_H_
#define _SELECT_SORT_H_

typedef SqList HeapType;	//堆采用顺序表存储表示

void SelectSort(SqList &L);
int SelectMinKey(SqList L, int i);
void HeapAdjust(HeapType &H, int s, int m);
void HeapSort(HeapType &H);
void HeapAdjust(HeapType &H, int s, int m);
void HeapSort(HeapType &H);

#endif