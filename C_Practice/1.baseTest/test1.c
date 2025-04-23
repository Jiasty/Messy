#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>

int main()
{
	//字符数组
	char arr1[] = "abc";
	char arr2[] = {'a', 'b', 'c'};
	char arr3[] = "abc\0def";
	printf("%s\n", arr1);
	printf("%s\n", arr2);
	printf("%s\n", arr3);

	//转义字符
	printf("%c %c\n", '\111', '\x30'); //八进制和十六进制专义。
	printf("This is a test file.\n\a");// \a为鸣笛转义字符。
	printf("asda\twoajsp\bfao\tspjfa\n");

	//计算字符串长度
	printf("%d %d\n", strlen("abc"), sizeof("abc"));

	printf("%d\n", strlen("C:\practice\test1\111.c")); //\p不是转义字符但是编译器还是认为它是一个字符

	//int n/*111*/um = 0; /*111*/被替换为空格
	//printf("%d\n", num);



	return 0;
}