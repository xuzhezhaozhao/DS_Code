#include <stdio.h>
#include <stdlib.h>

#include "my_headers.h"

int main()
{
	SString T, S1, S2, S3, Sub;
	char *p1 = "abc123abc";
	char *p2 = "abc";
	char *p3 = "xyzqp";
	StrAssign(S1, p1);
	StrAssign(S2, p2);
 	StrAssign(S3, p3);
 	Replace(S1, S2, S3);
	//StrInsert(S1, 1, S2);
	displayStr(S1);
	printf("\n%d\n", StrLength(S1));

	return 0;
}