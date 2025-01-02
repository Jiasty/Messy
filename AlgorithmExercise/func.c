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
}

void Change(ListNode** N1, ListNode** N2)
{
	ListNode* tmp = NULL;
	tmp = *N1;
	*N1 = *N2;
	*N2 = tmp;
}

void AdditionFunc()
{
	//�������뺯����������˫�������
	ListNode* Num1 = Enter("first");
	ListNode* Num2 = Enter("second");
	//��ʼ�Ӻ���ǰ��
	ListNode* cur1 = Num1->prev, * cur2 = Num2->prev;
	//�ж�һ�£�������λ�����Ķ�Ϊcur1������дһ�����ؽڵ�����ĺ�����
	if (cur1->NodeNum < cur2->NodeNum)
	{
		Change(&cur1, &cur2);
	}
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

	ListDestory(Num1);
	ListDestory(Num2);
}

void SubtractionFunc()
{
	//�������뺯����������˫�������
	ListNode* Num1 = Enter("first");
	ListNode* Num2 = Enter("second");
	ListNode* resultList = ListInit();
	//��ʼ�Ӻ���ǰ��
	int SignFlag = 0;
	ListNode* cur1 = Num1->prev, * cur2 = Num2->prev;
	//�����ϴ��תΪcur1�����������SignFlag��Ϊ1��
	if (cur1->NodeNum < cur2->NodeNum ||
		(cur1->NodeNum == cur2->NodeNum && strcmp(Num1->next->val, Num2->next->val) < 0)) 
	{
		Change(&cur1, &cur2);
		SignFlag = 1;
	}

	int byteCarry = 0;
	while (cur1 != Num1 || cur2 != Num2 || byteCarry != 0) {
		// ��ȡ��ǰ�ڵ��ֵ����������Ѿ���ͷ����Ĭ��Ϊ 0
		int num1 = (cur1 != Num1 && cur1->val) ? cur1->val[0] - '0' : 0;
		int num2 = (cur2 != Num2 && cur2->val) ? cur2->val[0] - '0' : 0;

		// ִ�м����������ǽ�λ
		int diff = num1 - num2 - byteCarry;
		if (diff < 0) {
			diff += 10;
			byteCarry = 1;
		}
		else {
			byteCarry = 0;
		}

		// �����ת��Ϊ�ַ�����������
		char diffStr[2] = { diff + '0', '\0' };
		ListPushFront(resultList, diffStr);

		// �ƶ���ǰһ���ڵ�
		cur1 = (cur1 != Num1) ? cur1->prev : Num1;
		cur2 = (cur2 != Num2) ? cur2->prev : Num2;
	}

	// �Ƴ���������е�ǰ����
	while (resultList->next != resultList && strcmp(resultList->next->val, "0") == 0) {
		ListNode* toDelete = resultList->next;
		resultList->next = toDelete->next;
		toDelete->next->prev = resultList;
		free(toDelete->val);
		free(toDelete);
	}

	// ����������Ϊ�գ�����һ�� "0"
	if (resultList->next == resultList) {
		ListPushFront(resultList, "0");
	}
	printf("The result is:");
	if (SignFlag == 1) printf("-");
	ListPrint(cur1);
}

// ����������������˫�����ʾ�������
ListNode* AddTwoLists(ListNode* List1, ListNode* List2)
{
	ListNode* Result = ListInit();
	ListNode* cur1 = List1->prev;
	ListNode* cur2 = List2->prev;
	int carry = 0;

	while (cur1 != List1 || cur2 != List2 || carry != 0)
	{
		int digit1 = (cur1 != List1) ? atoi(cur1->val) : 0;
		int digit2 = (cur2 != List2) ? atoi(cur2->val) : 0;
		long long sum = (long long)digit1 + digit2 + carry;

		carry = sum / 10000; // ���½�λ
		char buffer[5];
		sprintf(buffer, "%04d", (int)(sum % 10000)); // ��ʽ��Ϊ 4 λ
		ListPushFront(Result, buffer);

		if (cur1 != List1) cur1 = cur1->prev;
		if (cur2 != List2) cur2 = cur2->prev;
	}

	return Result;
}

void MultiplicationFunc()
{
	// �������뺯����������˫�������
	ListNode* Num1 = Enter("first");
	ListNode* Num2 = Enter("second");

	// �������˫������ʼ��Ϊ 0
	ListNode* Result = ListInit();
	ListPushFront(Result, "0");

	// ���ѭ���������ڶ�������ÿ���ڵ�
	ListNode* cur2 = Num2->prev;
	int shift = 0; // ƫ��������ʾ��λ�Ĳ� 0 ����
	while (cur2 != Num2)
	{
		// ��ǰ�ڵ�ֵ����Ϊ������4 λ��
		int digit2 = atoi(cur2->val);
		int carry = 0;

		// ��ʱ�������
		ListNode* TempResult = ListInit();

		// ���ƫ�� 0�������λ��
		for (int i = 0; i < shift; i++)
		{
			ListPushFront(TempResult, "0000");
		}

		// �ڲ�ѭ����������һ������ÿ���ڵ�
		ListNode* cur1 = Num1->prev;
		while (cur1 != Num1)
		{
			// ��ǰ�ڵ�ֵ����Ϊ������4 λ��
			int digit1 = atoi(cur1->val);
			long long product = (long long)digit1 * digit2 + carry;

			carry = product / 10000; // ���½�λ
			char buffer[5];
			sprintf(buffer, "%04d", (int)(product % 10000)); // ��ʽ��Ϊ 4 λ
			ListPushFront(TempResult, buffer);

			cur1 = cur1->prev;
		}

		// ������н�λ����ӵ���ʱ�������
		if (carry > 0)
		{
			char buffer[5];
			sprintf(buffer, "%04d", carry);
			ListPushFront(TempResult, buffer);
		}

		// �����ֻ��ӵ����ս��
		Result = AddTwoLists(Result, TempResult);

		// ������ʱ����
		ListDestory(TempResult);

		// ƫ��������
		shift++;
		cur2 = cur2->prev;
	}

	// ��ӡ���ս��
	printf("The result is: ");
	ListPrint(Result);

	// �ͷ������ڴ�
	ListDestory(Num1);
	ListDestory(Num2);
	ListDestory(Result);
}

