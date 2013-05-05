#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "my_headers.h"

int main()
{
	HashTable H;
	CreateHashTable(H, "HASH_TABLE.txt");
	DisplayHashTable(H);

	return 0;
}