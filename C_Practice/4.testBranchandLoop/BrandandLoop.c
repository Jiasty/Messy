#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void GuesstheNumber()
{
	int num = rand() % 101 + 1;
	int in = -1;
	printf("Guess the number(0 ~ 100): ");
	while (1)
	{
		(void)scanf("%d", &in);
		if (in > num)
			printf("����\n");
		else if (in < num)
			printf("С��\n");
		else
		{
			printf("����\n");
			break;
		}
	}
}

int main()
{
	/*srand((unsigned int)time(NULL));
	GuesstheNumber();*/

	//�߼���������·
	int n = 10;
	if (++n >= 5 || --n <= 1)
		printf("true, n: %d\n", n);
	if (++n >= 20 && --n <= 30)
		printf("true, n: %d\n", n);
	printf("n: %d\n", n);

	//switch
	int m = 2;
	switch (m)
	{
	case 0:
		printf("hehe\n");
	case 1:
		printf("hehe\n");
	case 2:
		printf("hehe\n");
	case 3:
		printf("hehe\n");
	default:
		printf("--------\n");
	}


	//goto���
	printf("hello\n");
goto next;
	printf("world\n");

next:
	printf("������world�Ĵ�ӡ\n");

	while (1)
	{
		while (1)
		{
			while (1)
			{
				goto next2;
			}
		}
	}

next2:
	printf("����������ѭ��\n");


	//��������
	int in = 0;
	//����scanf�ķ���ֵ����������ʱ����-1��
	//Ϊ�δ˴����벻���ϵ����ݻ���ѭ���������Ϸ���0���Ҳ����ϵ�����һֱ�ڻ��������´ζ�ȡ���ɷ���0.==EOF�Ż�����ѭ����
	//�Ҳ���ȷ�涨scanf�ķ���ֵΪ����ʱ����ctl+z����-1��Ҳ�Ƿ�0��Ҳ��������ѭ����
	while (scanf("%d", &in) != EOF) 
	{
		printf("%d\n", in);
	}

	return 0;
}