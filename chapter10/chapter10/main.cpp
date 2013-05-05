#include <stdio.h>

#include "my_headers.h"

int main()
{
	//SqList L;
	//CreateSqList(L, "SqList.txt");
	//int dlta[30] = {1};
	//int t = 1;
	//MergeSort(L);
	//for (int i = 1; i <= L.length; i++) {
	//	printf("%d ", L.elem[i]);
	//}
	float s,p=1.0;
	int i,n;
	printf("Put a number:");
	scanf("%d",&n);
	for (i=1;i<=n;++i) { 
		p*=((i)/(i+1.0)-(i+2)/(i+3.0));
	}
	printf("\n p=%f",p);
	return 0;
}