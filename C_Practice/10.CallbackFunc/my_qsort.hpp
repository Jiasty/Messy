#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Student
{
	int age;
	char name[10];
}Student;

int comparInt(const void* x, const void* y)
{
	return *(int*)x - *(int*)y;
	// return *(int*)y - *(int*)x;
}

int comparStubyAge(const void* x, const void* y)
{
	return ((Student*)x)->age - ((Student*)y)->age;
}

void Swap(char* x, char* y, int num)
{
	// @由于我们不知道传过来的是什么类型，我们采用单字节交换.
	for (int i = 0; i < num; i++)
	{
		char tmp = *x;
		*x = *y;
		*y = tmp;
		x++;
		y++;
	}
}

// 冒泡排序实现qsort
void my_qsort(void* base, size_t num, size_t size, int (*cmp)(const void*, const void*))
{
	_Bool flag = false;
	for (size_t i = 0; i < num - 1; i++)
	{
		for (size_t j = 0; j < num -1 - i; j++)
		{
			// 将base强转为char*方便计算偏移位置，以加减字节单位.
			if (cmp((char*)base + j * size, (char*)base + (j + 1) * size) > 0)
			{
				Swap((char*)base + j * size, (char*)base + (j + 1) * size, size);
				flag = true;
			}
		}
		if (!flag) return;
	}
}