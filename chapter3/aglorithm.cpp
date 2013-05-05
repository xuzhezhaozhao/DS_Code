/* 书本上第三章算法实现 */
#include <stdio.h>
#include <stdlib.h>

#include "type_def.h"
#include "sq_stack.h"
#include "aglorithm.h"

int count = 0;   //hanoi问题移动盘子的次数

/**
 * 算法3.1, 进制转换，10进制转8进制
 */
void conversion()
{
	int n;
	SElemType e;
	SqStack S;
	InitStack(S);
	printf("Input: ");
	scanf("%d", &n);
	while (n) {
		Push(S, n%8);
		n /= 8;
	}
	printf("Output: ");
	while (!StackEmpty(S)) {
		Pop(S, e);
		printf("%d", e);
	}
	printf("\n");
}

/**
 * P.49页，3.2.2 括号匹配的检验, 匹配返回OK，不匹配返回ERROR
 */
Status chectBracket(char *expr)
{
	int i = 0;
	SqStack S;
	InitStack(S);
	SElemType e;
	while ('\0' != *(expr+i)) {
		switch (*(expr+i)) {
		case '(':
			Push(S, -1);
			break;
		case '[':
			Push(S, -2);
			break;
		case '{':
			Push(S, -3);
			break;
		case ')':
			if (OK == GetTop(S, e)) {		//栈非空，得到栈顶元素
				if (-1 == e)			//栈顶元素与‘）’匹配
					Pop(S, e);		// 删除栈顶元素
				else				// 不匹配，返回ERROR
					return ERROR;
			} else 
				return ERROR;
			break;
		case ']':
			if (OK == GetTop(S, e)) { 
				if (-2 == e)
					Pop(S, e);
				else
					return ERROR;
			} else 
				return ERROR;
			break;
		case '}':
			if (OK == GetTop(S, e)) {
				if (-3 == e)
					Pop(S, e);
				else
					return ERROR;
			} else
				return ERROR;
			break;
		default:
			break;
		} //switch

		i++;
	} // while

	if (StackEmpty(S))
		return OK;
	else
		return ERROR;
}

/**
 * 算法3.2，行编辑程序，#: 退格，@: 清空该行, EOF: 退出
 */
void LineEdit()
{
	char ch;	//用户输入的字符
	int c;
	SqStack S;
	InitStack(S);
	ch = getchar();
	while (EOF != ch) {   //EOF为全文结束符, windows 下为ctrl+Z
		while (EOF != ch && '\n' != ch) {
			switch (ch) {
			case '#': 
				Pop(S, c);
				break;
			case '@':
				ClearStack(S);
				break;
			default:
				Push(S, ch);
				break;
			}
			ch = getchar();	
		}
		StackTraverse(S, display_char);
		printf("\n");
		ClearStack(S);
		if (EOF != ch)
			ch = getchar();
	} //while
}
Status display_char(SElemType e)
{
	printf("%c", e);
	return OK;
}

/**
 * 算法3.3 见chapter3_Maze工程
 */


/**
 * +、－、*、/优先级判断，表见P53
 */
char Precede(char c1, char c2)
{
	switch (c1) {
	case '+':
	case '-':
		switch (c2) {
		case '+':
		case '-':
		case ')':
		case '#':
			return '>';
			break;
		case '*':
		case '/':
		case '(':
			return '<';
			break;
		default:
			break;
		}
		break;
	case '*':
	case '/':
		switch (c2) {
		case '+':
		case '-':
		case '*':
		case '/':
		case ')':
		case '#':
			return '>';
			break;
		case '(':
			return '<';
			break;
		default:
			break;
		}
		break;
	case '(':
		switch (c2) {
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
			return '<';
			break;
		case ')':
			return '=';
			break;
		default:
			break;
		}
		break;
	case ')':
		switch (c2) {
		case '+':
		case '-':
		case '*':
		case '/':
		case ')':
		case '#':
			return '>';
			break;
		default:
			break;
		}
		break;
	case '#':
		switch (c2) {
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
			return '<';
			break;
		case '#':
			return '=';
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

/**
 * 判断字符c是否为操作符，是返回true,不是返回false
 */
bool In(char c)
{
	if ('+' == c || '-' == c || '/' == c || '*' == c 
		|| '(' == c || ')' == c || '#' == c)
		return true;
	return false;
}

/**
 * 运算
 */
int Operate(int a, char theta, int b)
{
	switch (theta) {
	case '+':
		return a+b;
		break;
	case '-':
		return a-b;
		break;
	case '*':
		return a*b;
		break;
	case '/':
		return a/b;
		break;
	default:
		break;
	}
	return ERROR;
}

/**
 * 算法3.4，算术表达式求值
 */
int EvaluateExpression()
{
	SqStack OPTR, OPND;
	InitStack(OPTR);
	Push(OPTR, '#');
	InitStack(OPND);
	int c, x;
	int theta;
	int a, b;
	c = getchar();
	while ('#' != c || GetTop(OPTR) != '#') {
		if (!In(c)) {     // c不是操作符
			c = c - '0';
			Push(OPND, c);
			c = getchar();
		} else {
			switch (Precede(GetTop(OPTR), c)) {
			case '<':   //栈顶元素优先级低
				Push(OPTR, c);
				c = getchar();
				break;
			case '=':   // 脱括号
				Pop(OPTR, x);
				c = getchar();
				break;
			case '>':    //栈顶元素优先级高，要先算，退栈并将运算结果入栈
				Pop(OPTR, theta);
				Pop(OPND, b);
				Pop(OPND, a);
				Push(OPND, Operate(a, theta, b));
				break;
			default:
				break;
			}
		} //else
	} //while
	return GetTop(OPND);       
}

/**
 * 移动盘子, 将编号为n的盘子从x移动到y
 */
void move(int &count, char x, int n, char y)
{
	count++;
	printf("%d. Move %d from %c to %c.\n", count, n, x, y);
}

/**
 * 算法，3.5，将编号从1至n的盘子从x移动到z
 */
void hanoi(int n, char x, char y, char z)
{
	if (1 == n)
		move(count, x, 1, z);
	else {
		hanoi(n-1, x, z, y);
		move(count, x, n, z);
		hanoi(n-1, y, x, z);
	}
}