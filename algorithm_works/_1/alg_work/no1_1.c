#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>

void func(int pageNum)
{
	int nums[10] = { 0 };
	//获取个位数
	
	for (int i = 1; i <= pageNum; i++)
	{
		int tmp = i;
		while (tmp)
		{
			nums[tmp % 10]++;
			tmp /= 10;
		}
	}

	FILE* f2;
	f2 = fopen("output.txt", "w");
	if (f2 == NULL) exit(-1);

	for (int i = 0; i < 10; i++)
	{
		fprintf(f2, "%d\n", nums[i]);
	}

	fclose(f2);
}

int main()
{
	FILE* f1;
	f1 = fopen("input.txt", "r");
	if (f1 == NULL) exit(-1);
	
	int pages = 0;
	fscanf(f1, "%d", &pages);
	printf("该书的总页码数为：%d\n", pages);
	func(pages);

	fclose(f1);
	return 0;
}