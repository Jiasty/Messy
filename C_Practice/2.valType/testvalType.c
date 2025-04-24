#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

int main()
{
	int a1 = 10;
	signed int a2 = 10;
	long b1;
	long int b2;
	long long c1;
	long long int c2;
	float d = 98.5f;
	double e = 98.5;
	_Bool flag = true;

	int max = INT_MAX;

	int m = 10;
	{
		int m = 20;
		printf("%d\n", m); //就近原则。
	}

	float a = 7 / 2; //先按整数算出来得3，再转为float。
	float b = 7.0 / 2;
	printf("%f %f\n", a, b);

	int n = (int)3.14;
	printf("%d\n", n);

	return 0;
}