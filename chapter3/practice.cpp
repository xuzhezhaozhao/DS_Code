#include <stdio.h>
#include <stdlib.h>

#include "my_headers.h"

/**
 * 习题3.19，在aglorithm.cpp中的Status chectBracket(char *expr)函数实现了
 */

/**
 * 习题3.21，将中序表达式写成逆波兰式
 */
void RPN(SqStack &S1, SqStack &S2)
{
	char c;
	int temp;
	InitStack(S1);		//存储临时运算符
	InitStack(S2);		//存储逆波兰式
	Push(S1, '#');
	c = getchar();
	while (c != '#' || !StackEmpty(S1)) {
		if (!In(c)) {		//不是运算符，是操作数
			Push(S2, c);
			c = getchar();	//读入下一个字符
		} else {		//是运算符
			if ('(' == c) {
				Push(S1, c);
				c = getchar();	//读入下一个字符
			} else if (')' == c) {
				while (GetTop(S1) != '(') {
					Pop(S1, temp);
					Push(S2, temp);
				}
				if (GetTop(S1) == '(')
					Pop(S1, temp);
				c = getchar();
			} else {
				switch (Precede(GetTop(S1), c)) {
				case '<':
					Push(S1, c);
					c = getchar();
					break;
				case '>':
					while ('>' == Precede(GetTop(S1), c)) {
						Pop(S1, temp);
						Push(S2, temp);
					}
					Push(S1, c);
					c = getchar();
					break;
				}
			}
		}
		if ('#' == c) {
			while ('#' != GetTop(S1)) {
				Pop(S1, temp);
				Push(S2, temp);
			}
			Pop(S1, temp);
		}
	
	}
}