#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

int main()
{
	//逻辑操作符短路
	int n = 10;
	if (++n >= 5 || --n <= 1)
		printf("true, n: %d\n", n);
	if (++n >= 20 && --n <= 30)
		printf("true, n: %d\n", n);
	printf("n: %d\n", n);

	//switch
	int m = 2;
	switch (m)
	{
	case 0:
		printf("hehe\n");
	case 1:
		printf("hehe\n");
	case 2:
		printf("hehe\n");
	case 3:
		printf("hehe\n");
	default:
		printf("--------\n");
	}


	//goto语句
	printf("hello\n");
goto next;
	printf("world\n");

next:
	printf("跳过了world的打印\n");

	while (1)
	{
		while (1)
		{
			while (1)
			{
				goto next2;
			}
		}
	}

next2:
	printf("跳出了三个循环\n");


	//多组输入
	int in = 0;
	//利用scanf的返回值，不想输入时返回-1。
	//为何此处输入不符合的内容会死循环？不符合返回0，且不符合的内容一直在缓冲区，下次读取依旧返回0.==EOF才会跳出循环。
	//且不明确规定scanf的返回值为多少时，当ctl+z返回-1，也是非0，也不会跳出循环。
	while (scanf("%d", &in) != EOF) 
	{
		printf("%d\n", in);
	}

	return 0;
}