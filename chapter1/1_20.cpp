//ϰ��1.20

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int *a;
	int x, n;
	int i;
	int p = 0;
	int temp = 1;

	printf("Input x: ");
	scanf("%d", &x);
	printf("Input n: ");
	scanf("%d", &n);
	printf("Input a[0]~a[n]: ");
	a = (int *)malloc(n*sizeof(int));	
	for(i=0; i<=n; i++)
	{
		scanf("%d", &a[i]);
	}
	for(i=0; i<=n; i++)
	{
		p += a[i]*temp;
		temp = temp*x;
	}

	printf("%d\n", p);
	return 0;
}
