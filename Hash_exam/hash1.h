#pragma once
#include <stdio.h>
#include <stdlib.h>

#define MaxSize 100			//定义最大哈希表长度
#define NULLKEY -1  //表示为空
typedef int KeyType;

typedef struct HashTable
{
    KeyType key;
    int count; //探测次数
} HashTable;

void InsertHT(HashTable ha[], int& n, int m, int p, KeyType k)  //将关键字k插入到哈希表中
{
    int cnt, adr;
    if (n == m)	return;//表空间已被占满

    adr = k % p;					//计算哈希函数值
    if (ha[adr].key == NULLKEY)	//k可以直接放在哈希表中
    {
        ha[adr].key = k;
        ha[adr].count = 1;
    }
    else						//发生冲突时采用线性探测法解决冲突
    {
        cnt = 1;					//cnt记录k发生冲突的次数
        while (ha[adr].key != NULLKEY && ha[adr].key != k)//防止重复插入相同关键字【教材上没写】
        {
            adr = (adr + 1) % m;	//线性探测
            cnt++;
        }

        if (ha[adr].key == k)	 return;//重复插入相同关键字【教材上没写】

        ha[adr].key = k;			//在adr处放置k
        ha[adr].count = cnt;		//设置探测次数
    }
    n++;						//总关键字个数增1
}
// 初始化哈希表
void CreateHT(HashTable ha[], int& n, int m, int p, KeyType keys[], int total)
{
    for (int i = 0; i < m; i++)				//哈希表置空的初值
    {
        ha[i].key = NULLKEY;
        ha[i].count = 0;
    }
    n = 0;
    for (int i = 0; i < total; i++)
        InsertHT(ha, n, m, p, keys[i]);		//插入n个关键字
}

// 哈希函数
int hashFunction(int key, int p)
{
    return key % p;
}



// 搜索元素
void SearchHT(HashTable ha[], int m, int p, KeyType k)  //在哈希表中查找关键字k
{
    int cnt = 1, adr;
    adr = k % p;					//计算哈希函数值
    while (ha[adr].key != NULLKEY && ha[adr].key != k && cnt < m)
    {
        cnt++;					//累计关键字比较次数
        adr = (adr + 1) % m;		//线性探测
    }
    if (ha[adr].key == k)			//查找成功
        printf("成功：关键字%d，比较%d次\n", k, cnt);
    else						//查找失败
        printf("失败：关键字%d，比较%d次\n", k, cnt);
}

// 删除元素
bool DeleteHT(HashTable ha[], int& n, int m, int p, KeyType k)	//删除哈希表中关键字k
{
    int cnt = 1, adr;
    adr = k % p;					//计算哈希函数值
    while (ha[adr].key != NULLKEY && ha[adr].key != k && cnt < m)
    {
        cnt++;					//累计关键字比较次数
        adr = (adr + 1) % m;		//线性探测
    }

    if (ha[adr].key == k)			//查找成功
    {
        ha[adr].key = NULLKEY;						//删除找到的该词
        ha[adr].count = 0;
        n--;											//哈希表中元素个数减少1

        int last_empty = adr;//记住清空项的位置：第一个空穴o
        int probe = (adr + 1) % m;   //probe为下一个可能存在试探adr的后继同义词待已删的元素位置#
        while (ha[probe].key != NULLKEY)//一直做到空位，才说明这个位置没人要，真的找完了。
        {									//由于删掉了一个元素，总能找到空位，不存在循环结束不了。
            int ideal = ha[probe].key % p; //求该元素本身该在的位置v，不考虑冲突后的右移 	
            if ((ideal <= last_empty && last_empty < probe) ||    //--v=o【=可以重复】#
                (probe < ideal && ideal <= last_empty) || //对于probe==ideal，说明是“正位”，不递补
                (last_empty < probe && probe < ideal)) //--o#
            {
                ha[last_empty].key = ha[probe].key;	//将同义词向前移动，补老空穴

                ha[last_empty].count = (ha[probe].count - (probe - last_empty)) % m;
                //填完空穴后在新位置，那么它的查找的次数count应该发生变化，
                //因为它移到空穴后相当于前移了，所以count会变小

                ha[probe].key = NULLKEY;//形成新空穴		
                last_empty = probe;//再指向新空穴

            }
            probe = (probe + 1) % m;       //继续试探循环后继位置 
        }
        return true;						//查找成功返回true 
    }
    else												//查找失败的情况 
        return false;									//返回false
}

void DispHT(HashTable ha[], int n, int m, int p)  //输出哈希表
{
    int i, j;
    int succ = 0, unsucc = 0, s;
    printf("哈希表:\n");
    printf(" 哈希表地址:\t");
    for (i = 0; i < m; i++)
        printf(" %3d", i);
    printf(" \n");
    printf(" 哈希表关键字:\t");
    for (i = 0; i < m; i++)
        if (ha[i].key == NULLKEY)
            printf("    ");			//输出3个空格
        else
            printf(" %3d", ha[i].key);
    printf(" \n");
    printf(" 探测次数:\t");
    for (i = 0; i < m; i++)
        if (ha[i].key == NULLKEY)
            printf("    ");			//输出3个空格
        else
            printf(" %3d", ha[i].count);
    printf(" \n");
}