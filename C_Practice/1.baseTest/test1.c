#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>

int main()
{
	//�ַ�����
	char arr1[] = "abc";
	char arr2[] = {'a', 'b', 'c'};
	char arr3[] = "abc\0def";
	printf("%s\n", arr1);
	printf("%s\n", arr2);
	printf("%s\n", arr3);

	//ת���ַ�
	printf("%c %c\n", '\111', '\x30'); //�˽��ƺ�ʮ������ר�塣
	printf("This is a test file.\n\a");// \aΪ����ת���ַ���
	printf("asda\twoajsp\bfao\tspjfa\n");

	//�����ַ�������
	printf("%d %d\n", strlen("abc"), sizeof("abc"));

	printf("%d\n", strlen("C:\practice\test1\111.c")); //\p����ת���ַ����Ǳ�����������Ϊ����һ���ַ�

	//int n/*111*/um = 0; /*111*/���滻Ϊ�ո�
	//printf("%d\n", num);



	return 0;
}