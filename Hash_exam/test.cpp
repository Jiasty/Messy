#define _CRT_SECURE_NO_WARNINGS 1
//#include"hash1.h"
#include"hash2.h"

//void test1()
//{
//	int keys[] = { 16,74,60,43,54,90,46,31,29,88,77 };
//	int n, m = 13, p = 13, k;//m为哈希表表长；p为哈希函数取余法的模长
//	HashTable ha[MaxSize];
//	printf("(1)创建哈希表\n"); CreateHT(ha, n, m, p, keys, 11);
//	printf("(2)显示哈希表:\n"); DispHT(ha, n, m, p);
//	k = 29;
//	printf("(3)查找"); SearchHT(ha, m, p, k);
//	k = 31;
//	printf("(4)删除：关键字%d\n", k);
//	DeleteHT(ha, n, m, p, k);
//	printf("(5)显示哈希表:\n"); DispHT(ha, n, m, p);
//	printf("(6)查找"); SearchHT(ha, m, p, k);
//	printf("(7)插入：关键字%d\n", k);
//	InsertHT(ha, n, m, p, k);
//	printf("(8)显示哈希表:\n"); DispHT(ha, n, m, p);
//	printf("\n");
//}

void test2()
{
	int keys[] = { 7,12,17,22 };
	int n, m = 5, k;
	HashTable ha[MaxSize];
	printf("(1)创建哈希表\n"); CreateHT(ha, n, m, keys, 4);
	printf("(2)显示哈希表:\n"); DispHT(ha, n, m);
	k = 12;
	printf("(3)查找"); SearchHT(ha, m, k);
	k = 7;
	printf("(4)删除：关键字%d\n", k);
	DeleteHT(ha, n, m, k);
	printf("(5)显示哈希表:\n"); DispHT(ha, n, m);
	printf("(6)查找"); SearchHT(ha, m, k);
	printf("(7)插入：关键字%d\n", k);
	InsertHT(ha, n, m, k);
	printf("(8)显示哈希表:\n"); DispHT(ha, n, m);
	printf("\n");
	DestroyHT(ha, m);		//销毁哈希表
}

int main() 
{
    test2();

    return 0;
}
