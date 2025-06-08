#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

typedef unsigned char* byte_pointer;

void show_byte(byte_pointer start, size_t len)
{
	for (int i = 0; i < len; i++)
	{
		printf("%.2x ", start[i]);
	}
	printf("\n");
}

void show_int(int num)
{
	show_byte(&num, sizeof(num));
}

void show_float(float num)
{
	show_byte(&num, sizeof(num));
}

void show_pointer(void* p)
{
	show_byte(&p, sizeof(p));
}


int main()
{
	int a = 10;
	float b = 20.1;
	int* p = &a;

	show_int(a);
	show_float(b);
	show_pointer(p);


	return 0;
}