#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

int main()
{
	double f = 0, c = 0;
	scanf("%lf", &f);
	c = 5 * (f - 32) / 9;
	printf("%.2lf", c);

	return 0;
}