#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

int main()
{
	int arr1[] = { 1,2,3,4,5 };
	//int arr1[5] = { 1,2,3,4,5 };
	int arr2[5];
	int arr3[5] = { 1,2,3 };
	int arr4[5] = { 0 }; //全初始化为0
	int arr5[5] = { 1 }; //只初始化一个
	for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); i++)
	{
		printf("%d ", arr1[i]);
		printf("%d ", arr2[i]);
		printf("%d ", arr3[i]);
		printf("%d ", arr4[i]);
		printf("%d ", arr5[i]);
		printf("\n");
	}
	printf("-------------------------------\n");

	//int size = 10;
	//int nums[n] = { 0 }; //变长数组，编译出错

	int nums[5] = { 0 };
	for (int i = 0; i < sizeof(nums) / sizeof(nums[0]); i++)
	{
		scanf("%d", &nums[i]); //arr[i]是数组中第i个元素，是一个具体的int变量,需要取地址。
	}
	for (int i = 0; i < sizeof(nums) / sizeof(nums[0]); i++)
	{
		printf("%d ", nums[i]);
	}

	printf("-------------------------------\n");

	int arr11[3][5] = { 0 };
	int arr22[][5] = { {1, 2, 3}, { 5, 6 }, { 78, 11 } };
	for (int i = 0; i < sizeof(arr22) / sizeof(arr22[0]); i++)
	{
		for (int j = 0; j < sizeof(arr22[0]) / sizeof(arr22[0][0]); j++)
		{
			printf("%d ", arr22[i][j]);
		}
		printf("\n");
	}


	return 0;
}