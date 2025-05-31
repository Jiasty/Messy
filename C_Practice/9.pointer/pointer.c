#define _CRT_SECURE_NO_WARNINGS 1
#define NDEBUG
#include <stdio.h>
#include <assert.h>

void print(int arr[], int size);
int Add(int x, int y);
int Sub(int x, int y);

typedef int(*pf)(int, int);

int main()
{
	// 指针变量大小
	int* p1;
	char* p2;
	long long* p3;
	printf("%d %d %d \n", sizeof(p1), sizeof(p2), sizeof(p3));

	// 指针类型的意义
	int n = 0x11111111;
	/*int* pn1 = &n;
	*pn1 = 0x22222222;*/
	char* pn2 = &n;
	*pn2 = 0x22222222;
	printf("%d\n", n);

	// const 修饰
	/*int m = 10;
	const int* pm1 = &m;
	*pm1 = 20;
	pm1 = &n;
	int* const pm2 = &m;
	*pm2 = 20;
	pn = &n;

	int x = 11;
	const int* const px = &x;
	*px = 20;
	px = NULL;*/

	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int* p = &arr[0]; // int* p = arr;
	int i = 0;
	int sz = sizeof(arr) / sizeof(arr[0]);
	while (p < arr + sz) //指针的⼤⼩⽐较
	{
		printf("%d ", *p);
		p++;
	}

	/*int* pp = NULL;
	assert(pp);*/


	// 指针访问数组的各种形式
	int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int* pa = a;
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", *(a + i));
		printf("%d ", pa[i]);
		printf("%d \n", i[a]);
	}

	// 一维数组传参
	int size = sizeof(a) / sizeof(a[0]);
	print(a, size);

	// 二级指针
	int num = 10;
	int* pnum = &num;
	int** ppnum = &pnum;
	printf("%d\n", **ppnum);
	printf("-----------------\n");

	// 字符指针
	char ch = 'a';
	char* pch = &ch;
	char* pch2 = "abcd";
	char* pch3 = "abcd";
	// const char* pch2 = "abcd";
	// *pch2 = "a"; 常量字符串不允许修改，且只会保存一份
	printf("%p %p %p\n", pch, pch2, pch3);


	// 数组指针变量
	int b[10];
	int(*pb)[10] = &b;

	int* pp = *pb; // pb解引用就是数组名，也就是首元素地址，可以用int*接收
	printf("%p %p\n", b, pp);


	// 函数指针变量
	int(*pAdd)(int, int) = Add;
	pf pAdd2 = Add;
	printf("%d %d %d\n", (*pAdd)(1, 2), pAdd(1, 2), pAdd2(1, 2));

	int(*farr[4])(int, int) = { Add, Sub };
	// pf farr[4] = { Add, Sub };
	printf("%d %d\n", farr[0](1, 2), farr[1](1, 2));

	return 0;
}

void print(int arr[], int size)
{
	// int size = sizeof(arr) / sizeof(arr[0]); // arr为首元素地址，此处算出来为1
	for (int i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int Add(int x, int y)
{
	return x + y;
}

int Sub(int x, int y)
{
	return x - y;
}