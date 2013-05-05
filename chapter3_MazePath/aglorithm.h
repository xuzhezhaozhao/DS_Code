#ifndef _AGLORITHM_H_
#define _AGLORITHM_H_
bool Pass(PosType curpos);
void FootPrint(PosType curpos);
PosType NextPos(PosType pos, int di);
Status MazePath(PosType start, PosType end);
Status display_path(SElemType e);
#endif