#define _CRT_SECURE_NO_WARNINGS 1
#include "my_qsort.hpp"

void test1()
{
	int a[] = { 1, 23, 41, 2, 121, 123, 9, 0 };
	int size = sizeof(a) / sizeof(a[0]);

	// qsort(a, size, sizeof(a[0]), compar);
	my_qsort(a, size, sizeof(a[0]), comparInt);

	for (int i = 0; i < size; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n----------------\n");
}

void test2()
{
	Student stu[] = { {10, "aa"}, {18, "cc"}, {12, "bb"} };
	int sz = sizeof(stu) / sizeof(stu[0]);

	my_qsort(stu, sz, sizeof(stu[0]), comparStubyAge);
	for (int i = 0; i < sz; i++)
	{
		printf("%d %s ", stu[i].age, stu[i].name);
	}
	printf("\n----------------\n");
}

int main()
{
	test1();
	test2();

	return 0;
}