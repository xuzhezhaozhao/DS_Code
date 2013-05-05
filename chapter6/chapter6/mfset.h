#ifndef _MFSET_H_
#define _MFSET_H_

typedef PTree MFSet;

int find_mfset(MFSet S, int i);
Status merge_mfset(MFSet &S, int i, int j);

#endif