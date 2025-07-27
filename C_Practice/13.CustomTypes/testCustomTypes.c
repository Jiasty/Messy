#define _CRT_SECURE_NO_WARNINGS 1
#pragma pack(1)
#pragma pack()
#include <stdio.h>
#include <stddef.h>

void testStruct()
{
	// �ṹ�嶨��
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

	// �����ṹ��
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

	p = &x; // ��ʵ�����ǲ�ͬ���͡�
	printf("%p %p\n", p, &x);


	// �ṹ��������
	//struct Node
	//{
	//	int data;
	//	struct Node next; // next������data��next,��Զ�㲻����С
	//};

	struct Node
	{
		int data;
		struct Node* next;
	};

	//typedef struct
	//{
	//	int data;
	//	Node* next; // ������ǰʹ���Զ�����
	//}Node;


	// �ṹ���ڴ����
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

	printf("%d\n", offsetof(struct S1, i)); //����ƫ����

	// λ�ε�ʵ��
	
	struct Bit
	{
		int a : 2;
		int b : 4;
		int c : 5;
		int d : 4;
	}; // ռ4B
	printf("struct Bit���͵Ĵ�СΪ:%d\n", sizeof(struct Bit));

	struct Bit sbit;

	// scanf("%d", &sbit.b); ����ֵ��ʽ

	int tmp = 2;
	sbit.b = tmp;
	printf("%d\n", sbit.b);
}

void testUnion()
{
	// �����嶨��
	union Un
	{
		char c;
		int i;
	};

	union Un un = { 0 };
	printf("%p\n", &(un.i));
	printf("%p\n", &(un.c));
	printf("%p\n", &un);

	// �������С����
	union U
	{
		int i;  // ������4
		char chs[7];  // ����������Ա��С���Ƚ� 1 < 8����˶�����Ϊ1
	};
	printf("%d\n", sizeof(union U));

	// �жϴ�С��
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
		Mon = 100,  // 0 Ĭ�������
		Tues, // 1
		Wed,  // 2
		Thur,
		Fri,
		Sat,
		Sun
	};

	enum Day e1 = Fri;
	// enum Day e3 = 1000;
	// enum Day e2 = 101; C���Բ��ᱨ��
	printf("%d %d\n", e1, sizeof(enum Day));
}


int main()
{
	testStruct();

	testUnion();

	testEnum();

	return 0;
}