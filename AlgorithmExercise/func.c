#define _CRT_SECURE_NO_WARNINGS 1

#include"func.h"

//提供功能选择并调用
void Menu()
{
	int choose = -1;
	printf("Please choose your want:\n");
	printf("1.Addition\n2.Subtraction\n3.Multiplication\n");
	(void)scanf("%d", &choose);

	if (choose == 1) AdditionFunc();
	else if (choose == 2) SubtractionFunc();
	else if (choose == 3) MultiplicationFunc();
	else printf("No this func!\n");
}

//输入数字，存入一个双链表并返回
ListNode* Enter(char* No)
{
	printf("Please enter in groups of four from end to end:\n");
	ListNode* head = ListInit();

	char temp[5]; //四位为一组，注意要有\0的位置
	char flag = 'y';
	while (flag == 'y')
	{
		(void)scanf("%4s", temp); //限制输入4个字符
		ListPushFront(head, temp);

		printf("Continue enter? y/n\n");
		(void)scanf(" %c", &flag); //%c前面加空格跳过上面输入时回车留下的空格
	}
	//???判断数字是否有效
	printf("The %s num is:", No);
	ListPrint(head);
	return head;
}

void int_to_string(char tmp[], int num)
{
	tmp[4] = '\0';
	for (int i = 3; i >= 0; i--)
	{
		tmp[i] = num % 10 + '0';
		num /= 10;
	}
	return tmp;
}

void AdditionFunc()
{
	//调用输入函数并用两个双链表接收
	ListNode* Num1 = Enter("first");
	ListNode* Num2 = Enter("second");
	//开始从后往前加
	ListNode* cur1 = Num1->prev, * cur2 = Num2->prev;
	//判断一下，尽量将位数长的定为cur1（链表写一个返回节点个数的函数）
	int Carry = 0;
	while (cur1 != Num1 && cur2 != Num2)
	{
		char* tmp1 = cur1->val;
		char* tmp2 = cur2->val;
		int num1 = 0, num2 = 0;
		for (int i = 0; tmp1[i] != '\0'; i++)
		{
			//终止条件为tmp1[i] != '\0'避免不到四位的一组计算错误
			num1 *= 10;
			num1 += tmp1[i] - '0';
		}
		for (int i = 0; tmp2[i] != '\0'; i++)
		{
			num2 *= 10;
			num2 += tmp2[i] - '0';
		}
		printf("%4d %4d\n", num1, num2);
		num1 = num1 + num2 + Carry;
		char tmp[5];
		int_to_string(tmp, num1);
		strncpy(cur1->val, tmp, 4);
		Carry = num1 / 10000;

		cur1 = cur1->prev;
		cur2 = cur2->prev;
	}
	if (Carry != 0)
	{
		int num = 0;
		for (int i = 0; cur1->val[i] != '\0'; i++)
		{
			num *= 10;
			num += cur1->val[i] - '0';
		}
		char tmp[5];
		int_to_string(tmp, num);
		strncpy(cur1->val, tmp, 4);
	}
	printf("The result is:");
	ListPrint(Num1);
}

void SubtractionFunc()
{
	//调用输入函数并用两个双链表接收
	ListNode* Num1 = Enter("first");
	ListNode* Num2 = Enter("second");
	//开始从后往前减
	ListNode* cur1 = Num1->prev, * cur2 = Num2->prev;


}

void MultiplicationFunc()
{
	//调用输入函数并用两个双链表接收
	ListNode* Num1 = Enter("first");
	ListNode* Num2 = Enter("second");
}