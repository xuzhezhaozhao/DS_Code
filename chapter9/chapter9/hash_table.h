#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

/* 开放定址哈希表的存储结构 */

typedef struct {
	ElemType *elem;		//数据元素基址
	int count;		//当前数据元素个数
	int sizeindex;		//hashsize[sizeindex]为当前容量
}HashTable;

#define NULLKEY UINT_MAX	//哈希表的位置为空的标志
#define SUCCESS 1
#define UNSUCCESS 0
#define DUPLICATE -1


Status SearchHash(HashTable &H, KeyType K, int &p, int &c);
int Hash(KeyType K, int p);
Status collision(int &p, int c, int len);
Status InsertHash(HashTable &H, ElemType e);
Status RecreateHashTable(HashTable &H);
Status InitHashTable(HashTable &H);
void DisplayHashTable(HashTable H);
Status CreateHashTable(HashTable &H, char *filename);

#endif