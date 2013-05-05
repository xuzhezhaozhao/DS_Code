//习题1.19
/* ◆1.19④ 试编写算法，计算i!×2^i的值并存入数组   
a[0..ARRSIZE-1]的第i-1个分量中 (i=1,2,…,n)。   
假设计算机中允许的整数最大值为MAXINT，则当n>   
ARRSIZE或对某个k(1≤k≤n)使k!×2^k>MAXINT时，应   
按出错处理。注意选择你认为较好的出错处理方法。*/

#include <stdio.h>
#define arrsize 40
#define MAXINT 65535

void main()
{
	int n, i, j;
	int a[arrsize];
	int temp = 1;
	bool flag = true;

	printf("please input n: ");
	scanf("%d", &n);

	if(n > arrsize)
	{
		flag = false;
	}

	for(i=0; i<n && flag; i++)
	{
		temp = 1;
		for(j=i; j>0 && flag; j--)
		{
			if(temp > MAXINT/(2*j))
			{
				flag = false;
			}
			temp *= 2*j;
		}
		if(0 == i)
		{
			a[i] = 1;
		}
		else
		{
			a[i] = temp;
		}
	}

	for(i=0; i<n && flag; i++)
	{
		printf("%d\t", a[i]);
	}
	if(!flag)
	{
		printf("Input wrong!");
	}
	printf("\n");
}