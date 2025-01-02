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
	//调用输入函数并用两个双链表接收
	ListNode* Num1 = Enter("first");
	ListNode* Num2 = Enter("second");
	//开始从后往前加
	ListNode* cur1 = Num1->prev, * cur2 = Num2->prev;
	//判断一下，尽量将位数长的定为cur1（链表写一个返回节点个数的函数）
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

	ListDestory(Num1);
	ListDestory(Num2);
}

void SubtractionFunc()
{
	//调用输入函数并用两个双链表接收
	ListNode* Num1 = Enter("first");
	ListNode* Num2 = Enter("second");
	ListNode* resultList = ListInit();
	//开始从后往前减
	int SignFlag = 0;
	ListNode* cur1 = Num1->prev, * cur2 = Num2->prev;
	//将数较大的转为cur1，如果交换则将SignFlag置为1。
	if (cur1->NodeNum < cur2->NodeNum ||
		(cur1->NodeNum == cur2->NodeNum && strcmp(Num1->next->val, Num2->next->val) < 0)) 
	{
		Change(&cur1, &cur2);
		SignFlag = 1;
	}

	int byteCarry = 0;
	while (cur1 != Num1 || cur2 != Num2 || byteCarry != 0) {
		// 提取当前节点的值，如果链表已经到头，则默认为 0
		int num1 = (cur1 != Num1 && cur1->val) ? cur1->val[0] - '0' : 0;
		int num2 = (cur2 != Num2 && cur2->val) ? cur2->val[0] - '0' : 0;

		// 执行减法，并考虑借位
		int diff = num1 - num2 - byteCarry;
		if (diff < 0) {
			diff += 10;
			byteCarry = 1;
		}
		else {
			byteCarry = 0;
		}

		// 将结果转换为字符并存入链表
		char diffStr[2] = { diff + '0', '\0' };
		ListPushFront(resultList, diffStr);

		// 移动到前一个节点
		cur1 = (cur1 != Num1) ? cur1->prev : Num1;
		cur2 = (cur2 != Num2) ? cur2->prev : Num2;
	}

	// 移除结果链表中的前导零
	while (resultList->next != resultList && strcmp(resultList->next->val, "0") == 0) {
		ListNode* toDelete = resultList->next;
		resultList->next = toDelete->next;
		toDelete->next->prev = resultList;
		free(toDelete->val);
		free(toDelete);
	}

	// 如果结果链表为空，插入一个 "0"
	if (resultList->next == resultList) {
		ListPushFront(resultList, "0");
	}
	printf("The result is:");
	if (SignFlag == 1) printf("-");
	ListPrint(cur1);
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
		shift++;
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

