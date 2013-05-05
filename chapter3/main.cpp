#include <stdio.h>
#include <stdlib.h>

#include "my_headers.h"

int main()
{
	SqStack S1, S2;
	RPN(S1, S2);

	StackTraverse(S2, display_char);

	return 0;
}