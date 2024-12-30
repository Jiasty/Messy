#define _CRT_SECURE_NO_WARNINGS 1

#include"func.h"

//�ṩ����ѡ�񲢵���
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

//�������֣�����һ��˫��������
ListNode* Enter(char* No)
{
	printf("Please enter in groups of four from end to end:\n");
	ListNode* head = ListInit();

	char temp[5]; //��λΪһ�飬ע��Ҫ��\0��λ��
	char flag = 'y';
	while (flag == 'y')
	{
		(void)scanf("%4s", temp); //��������4���ַ�
		ListPushFront(head, temp);

		printf("Continue enter? y/n\n");
		(void)scanf(" %c", &flag); //%cǰ��ӿո�������������ʱ�س����µĿո�
	}
	//???�ж������Ƿ���Ч
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
	//�������뺯����������˫�������
	ListNode* Num1 = Enter("first");
	ListNode* Num2 = Enter("second");
	//��ʼ�Ӻ���ǰ��
	ListNode* cur1 = Num1->prev, * cur2 = Num2->prev;
	//�ж�һ�£�������λ�����Ķ�Ϊcur1������дһ�����ؽڵ�����ĺ�����
	int Carry = 0;
	while (cur1 != Num1 && cur2 != Num2)
	{
		char* tmp1 = cur1->val;
		char* tmp2 = cur2->val;
		int num1 = 0, num2 = 0;
		for (int i = 0; tmp1[i] != '\0'; i++)
		{
			//��ֹ����Ϊtmp1[i] != '\0'���ⲻ����λ��һ��������
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
	//�������뺯����������˫�������
	ListNode* Num1 = Enter("first");
	ListNode* Num2 = Enter("second");
	//��ʼ�Ӻ���ǰ��
	ListNode* cur1 = Num1->prev, * cur2 = Num2->prev;


}

void MultiplicationFunc()
{
	//�������뺯����������˫�������
	ListNode* Num1 = Enter("first");
	ListNode* Num2 = Enter("second");
}