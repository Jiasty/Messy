#define _CRT_SECURE_NO_WARNINGS 1

#include"func.h"

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

ListNode* Enter(char* No)
{
	printf("Please enter in groups of four from end to end:\n");
	ListNode* head = ListInit();

	char temp[5];
	int flag = 1;
	while (flag == 1)
	{
		(void)scanf("%s", temp);
		ListPushFront(head, temp);

		printf("Continue enter? 1/0\n");
		(void)scanf("%d", &flag);
	}
	printf("The %s num is:", No);
	ListPrint(head);
	return head;
}

void AdditionFunc()
{
	//调用输入函数并用两个双链表接收
	ListNode* Num1 = Enter("first");
	ListNode* Num2 = Enter("second");
	
	


}

void SubtractionFunc()
{
	//调用输入函数并用两个双链表接收
	ListNode* Num1 = Enter("first");
	ListNode* Num2 = Enter("second");
}

void MultiplicationFunc()
{
	//调用输入函数并用两个双链表接收
	ListNode* Num1 = Enter("first");
	ListNode* Num2 = Enter("second");
}