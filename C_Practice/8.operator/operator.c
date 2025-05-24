#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

int main()
{
	int num1 = 017, num2 = 0x17;
	printf("%d %d\n", num1, num2);

	printf("%d\n", -2 >> 3);
	// int n = 20;
	// n >> -1;

	int a = 1;
	int b = 2;
	int c = (a > b, a = b + 10, b = a + 1);
	// c = b = 13
	printf("%d\n", c);

	int d = 1;
	if (a = b + 1, c = a / 2, d > 0) // 减少代码臃肿

	printf("%zd\n", sizeof d);
	int m = sizeof (long long);
	// int m = sizeof long long; 计算类型要加括号



	return 0;
}