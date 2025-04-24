#define _CRT_SECURE_NO_WARNINGS 1
//#pragma warning(disable: 4996)

#include <stdio.h>
int main()
{
	printf("hahahaha\nhehehehe\n");

	size_t n = 20;
	printf("%zd\n", n);
	printf("%x\n", n);


	printf("%5d\n", 123);
	printf("%-5d %5d\n", 123, 123);
	printf("%8f\n", 3.14);
	printf("%12f\n", 123.45);
	printf("%+d\n", 128);
	printf("%6.4f\n", 3.1415926);
	printf("%*.*f\n", 6, 4, 3.1415926);
	printf("%.5s\n", "hello world");

	/*int x = 0;
	scanf("%d", &x);*/

	/*char arr[5] = { 0 };
	scanf("%4s", arr);
	printf("%s", arr);*/

	/*int a = 0;
	int b = 0;
	float f = 0.0;
	int r = scanf("%d %d %f", &a, &b, &f);
	
	printf("a = %d\n", a);
	printf("b = %d\n", b);
	printf("f = %f\n", f);
	printf("r = %d\n", r);*/

	/*char ch = 0;
	scanf(" %c", &ch);
	scanf("%c", &ch);
	
	printf("%c", ch);
	printf("xxxx\n");
	return 0;*/

	/*int year = 0;
	int month = 0;
	int day = 0;
	scanf("%d%*c%d%*c%d", &year, &month, &day);
	printf("%d %d %d\n", year, month, day);*/

	return 0;
}