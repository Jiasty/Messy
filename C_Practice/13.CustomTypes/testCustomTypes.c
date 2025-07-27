#define _CRT_SECURE_NO_WARNINGS 1
#pragma pack(1)
#pragma pack()
#include <stdio.h>
#include <stddef.h>

void testStruct()
{
	// 结构体定义
	struct A
	{
		int i;
		char c;
	};

	struct A a = { 4, 'a' };

	struct
	{
		int id;
		char* name;
	}stus[10];

	for (int i = 0; i < sizeof(stus) / sizeof(stus[0]); i++)
	{
		stus[i].id = i;
		stus[i].name = "name-" + i;
	}

	// 匿名结构体
	struct
	{
		int a;
		char b;
	}x;
	struct
	{
		int a;
		char b;
	}*p;

	p = &x; // 其实他们是不同类型。
	printf("%p %p\n", p, &x);


	// 结构体自引用
	//struct Node
	//{
	//	int data;
	//	struct Node next; // next中又有data和next,永远算不出大小
	//};

	struct Node
	{
		int data;
		struct Node* next;
	};

	//typedef struct
	//{
	//	int data;
	//	Node* next; // 不可提前使用自定义名
	//}Node;


	// 结构体内存对齐
	struct S1
	{
		char c1;  // 1 8 1
		int i;    // 4 8 4
		char c2;  // 1 8 1
	};
	printf("%d\n", sizeof(struct S1)); //12
	struct S2
	{
		char c1;
		char c2;
		int i;
	};
	printf("%d\n", sizeof(struct S2)); //8

	printf("%d\n", offsetof(struct S1, i)); //计算偏移量

	// 位段的实现
	
	struct Bit
	{
		int a : 2;
		int b : 4;
		int c : 5;
		int d : 4;
	}; // 占4B
	printf("struct Bit类型的大小为:%d\n", sizeof(struct Bit));

	struct Bit sbit;

	// scanf("%d", &sbit.b); 错误赋值方式

	int tmp = 2;
	sbit.b = tmp;
	printf("%d\n", sbit.b);
}

void testUnion()
{
	// 联合体定义
	union Un
	{
		char c;
		int i;
	};

	union Un un = { 0 };
	printf("%p\n", &(un.i));
	printf("%p\n", &(un.c));
	printf("%p\n", &un);

	// 联合体大小计算
	union U
	{
		int i;  // 对齐数4
		char chs[7];  // 对齐数按成员大小来比较 1 < 8，因此对齐数为1
	};
	printf("%d\n", sizeof(union U));

	// 判断大小端
	union
	{
		int i;
		char c;
	}unnnn;
	unnnn.i = 1;
	printf("%d\n", unnnn.c);
}

void testEnum()
{
	enum Day
	{
		Mon = 100,  // 0 默认情况下
		Tues, // 1
		Wed,  // 2
		Thur,
		Fri,
		Sat,
		Sun
	};

	enum Day e1 = Fri;
	// enum Day e3 = 1000;
	// enum Day e2 = 101; C语言不会报错
	printf("%d %d\n", e1, sizeof(enum Day));
}


int main()
{
	testStruct();

	testUnion();

	testEnum();

	return 0;
}