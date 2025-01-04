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
        int F = 0;
		(void)scanf("%4s", temp); //限制输入4个字符
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
		(void)scanf(" %c", &flag); //%c前面加空格跳过上面输入时回车留下的空格
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
    //printf("num value: %d, calculated string length: %d\n", num, n);  // 添加这行调试输出语句
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

void AdditionFunc() //此加法函数可以调用后面的辅助函数替换
{
	//调用输入函数并用两个双链表接收
	ListNode* Num1 = Enter("first");
	ListNode* Num2 = Enter("second");
	//开始从后往前加
	ListNode* cur1 = Num1->prev, * cur2 = Num2->prev;
	//判断一下，尽量将位数长的定为cur1（链表写一个返回节点个数的函数）
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

	//释放链表
	ListDestory(Num1);
	ListDestory(Num2);
}

void SubtractionFunc()
{
    //调用输入函数并用两个双链表接收
    ListNode* Num1 = Enter("first");
    ListNode* Num2 = Enter("second");
    ListNode* Result = ListInit();
    //开始从后往前减
    int SignFlag = 0;
    ListNode* cur1 = Num1->prev, * cur2 = Num2->prev;
    //将数较大的转为cur1，如果交换则将SignFlag置为1。
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
        // 提取当前节点的值，如果链表已经到头，则默认为 0
        int num1 = (cur1 != Num1 && cur1->val) ? atoi(cur1->val) : 0;
        int num2 = (cur2 != Num2 && cur2->val) ? atoi(cur2->val) : 0;

        // 执行减法，并考虑借位
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

        // 将结果转换为字符并存入链表
        char tmp[5];
        int_to_string(tmp, diff);
        ListPushFront(Result, tmp);

        // 移动到前一个节点
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

// 辅助函数：将两个双链表表示的数相加
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

        carry = sum / 10000; // 更新进位
        char buffer[5];
        sprintf(buffer, "%04d", (int)(sum % 10000)); // 格式化为 4 位
        ListPushFront(Result, buffer);

        if (cur1 != List1) cur1 = cur1->prev;
        if (cur2 != List2) cur2 = cur2->prev;
    }

    return Result;
}
void MultiplicationFunc()
{
    // 调用输入函数并用两个双链表接收
    ListNode* Num1 = Enter("first");
    ListNode* Num2 = Enter("second");

    // 创建结果双链表，初始化为 0
    ListNode* Result = ListInit();
    ListPushFront(Result, "0");

    // 外层循环：遍历第二个数的每个节点
    ListNode* cur2 = Num2->prev;
    int shift = 0; // 偏移量，表示低位的补 0 数量
    while (cur2 != Num2)
    {
        // 当前节点值解析为整数（4 位）
        int digit2 = atoi(cur2->val);
        int carry = 0;

        // 临时结果链表
        ListNode* TempResult = ListInit();

        // 添加偏移 0（补齐低位）
        for (int i = 0; i < shift; i++)
        {
            ListPushFront(TempResult, "0000");
        }

        // 内层循环：遍历第一个数的每个节点
        ListNode* cur1 = Num1->prev;
        while (cur1 != Num1)
        {
            // 当前节点值解析为整数（4 位）
            int digit1 = atoi(cur1->val);
            long long product = (long long)digit1 * digit2 + carry;

            carry = product / 10000; // 更新进位
            char buffer[5];
            sprintf(buffer, "%04d", (int)(product % 10000)); // 格式化为 4 位
            ListPushFront(TempResult, buffer);

            cur1 = cur1->prev;
        }

        // 如果还有进位，添加到临时结果链表
        if (carry > 0)
        {
            char buffer[5];
            sprintf(buffer, "%04d", carry);
            ListPushFront(TempResult, buffer);
        }

        // 将部分积加到最终结果
        Result = AddTwoLists(Result, TempResult);

        // 清理临时链表
        ListDestory(TempResult);

        // 偏移量增加
        shift++; //1:4
        cur2 = cur2->prev;
    }

    // 打印最终结果
    printf("The result is: ");
    ListPrint(Result);

    // 释放链表内存
    ListDestory(Num1);
    ListDestory(Num2);
    ListDestory(Result);
}