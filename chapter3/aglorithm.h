/* 书本上第三章算法实现 */
#ifndef _AGLORITHM_H_
#define _AGLORITHM_H_

void conversion();
Status chectBracket(char *expr);
void LineEdit();
Status display_char(SElemType e);
char Precede(char c1, char c2);
bool In(char c);
int EvaluateExpression();
void move(int &count, char x, int n, char y);
void hanoi(int n, char x, char y, char z);


#endif