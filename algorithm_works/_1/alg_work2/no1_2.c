#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>

int Div(int num)
{
	int ret = 0;
	for (int i = 1; i <= num; i++)
		if (num % i == 0) ret++;

	return ret;
}

int main()
{
	FILE* f1;
	f1 = fopen("input.txt", "r");
	if (f1 == NULL) exit(-1);

	int num1, num2;
	fscanf(f1, "%d %d", &num1, &num2);
	printf("两个数为：%d %d", num1, num2);
	fclose(f1);

	FILE* f2;
	f2 = fopen("output.txt", "w");
	fprintf(f2, "%d", max(Div(num1), Div(num2)));
	fclose(f2);

	return 0;
}