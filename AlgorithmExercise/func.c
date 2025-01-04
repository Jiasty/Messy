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
        int F = 0;
		(void)scanf("%4s", temp); //��������4���ַ�
        for (int i = 0; temp[i]; i++)
            if (temp[i] < '0' || temp[i] > '9')
            {
                F = 1;
                break;
            }
        if (F == 0) ListPushFront(head, temp);
        else
        {
            printf("This group is error!\n");
        }

		printf("Continue enter? y/n\n");
		(void)scanf(" %c", &flag); //%cǰ��ӿո�������������ʱ�س����µĿո�
	}
	printf("The %s num is:", No);
	ListPrint(head);
	return head;
}

void int_to_string(char tmp[], int num)
{
	int n = 0;
	int tmpNum = num;
	while (tmpNum)
	{
		n++;
		tmpNum /= 10;
	}
    //printf("num value: %d, calculated string length: %d\n", num, n);  // ������е���������
	tmp[n] = '\0';
	for (int i = n - 1; i >= 0; i--)
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

void AdditionFunc() //�˼ӷ��������Ե��ú���ĸ��������滻
{
	//�������뺯����������˫�������
	ListNode* Num1 = Enter("first");
	ListNode* Num2 = Enter("second");
	//��ʼ�Ӻ���ǰ��
	ListNode* cur1 = Num1->prev, * cur2 = Num2->prev;
	//�ж�һ�£�������λ�����Ķ�Ϊcur1������дһ�����ؽڵ�����ĺ�����
	if (countNodes(cur1) < countNodes(cur2))
	{
		Change(&cur1, &cur2);
	}
	int Carry = 0;
	while (cur1 != Num1 && cur2 != Num2)
	{
		int num1 = atoi(cur1->val), num2 = atoi(cur2->val);

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
		int num = atoi(cur1->val);
		char tmp[5];
		int_to_string(tmp, num);
		strncpy(cur1->val, tmp, 4);
	}
	printf("The result is:");
	ListPrint(Num1);

	//�ͷ�����
	ListDestory(Num1);
	ListDestory(Num2);
}

void SubtractionFunc()
{
    //�������뺯����������˫�������
    ListNode* Num1 = Enter("first");
    ListNode* Num2 = Enter("second");
    ListNode* Result = ListInit();
    //��ʼ�Ӻ���ǰ��
    int SignFlag = 0;
    ListNode* cur1 = Num1->prev, * cur2 = Num2->prev;
    //�����ϴ��תΪcur1�����������SignFlag��Ϊ1��
    if (countNodes(Num1) < countNodes(Num2) ||
        (countNodes(Num1) == countNodes(Num2) && strcmp(Num1->next->val, Num2->next->val) < 0))
    {
        Change(&Num1, &Num2);
        cur1 = Num1->prev, cur2 = Num2->prev;
        SignFlag = 1;
    }

    int byteCarry = 0;
    while (cur1 != Num1 || cur2 != Num2 || byteCarry != 0)
    {
        // ��ȡ��ǰ�ڵ��ֵ����������Ѿ���ͷ����Ĭ��Ϊ 0
        int num1 = (cur1 != Num1 && cur1->val) ? atoi(cur1->val) : 0;
        int num2 = (cur2 != Num2 && cur2->val) ? atoi(cur2->val) : 0;

        // ִ�м����������ǽ�λ
        int diff = num1 - num2 - byteCarry;
        if (diff < 0) 
        {
            diff += 10000;
            byteCarry = 1;
        }
        else 
        {
            byteCarry = 0;
        }

        // �����ת��Ϊ�ַ�����������
        char tmp[5];
        int_to_string(tmp, diff);
        ListPushFront(Result, tmp);

        // �ƶ���ǰһ���ڵ�
        cur1 = (cur1 != Num1) ? cur1->prev : Num1;
        cur2 = (cur2 != Num2) ? cur2->prev : Num2;
    }

    printf("The result is:");
    if (SignFlag == 1) printf("-");
    ListPrint(Result);

    ListDestory(Num1);
    ListDestory(Num2);
    ListDestory(Result);
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
        shift++; //1:4
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