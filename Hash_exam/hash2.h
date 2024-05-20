#pragma once
//����������Ĺ�ϣ��������㷨
#include <stdio.h>
#include <malloc.h>
#define MaxSize 100				//��������ϣ����

typedef int KeyType;			//�ؼ�������

typedef struct node
{
	KeyType key;				//�ؼ�����
	struct node* next;			//��һ�����ָ��
} NodeType;						//������������

typedef struct
{
	NodeType* firstp;			//�׽��ָ��
} HashTable;		//��ϣ������    ��ע����ʽ��ջ�����С����Ա�Ҳ�Ƽ����ַ�װ��


void InsertHT(HashTable ha[], int& n, int m, KeyType k)  //���ؼ���k���뵽��ϣ����
{
	int adr;
	adr = k % m;					//�����ϣ����ֵ

	NodeType* q;
	q = (NodeType*)malloc(sizeof(NodeType));
	q->key = k;					//����һ�����q����Źؼ���k
	q->next = NULL;

	if (ha[adr].firstp == NULL)	//��������adrΪ��
		ha[adr].firstp = q;
	else						//��������adr����
	{
		q->next = ha[adr].firstp;	//����ͷ�巨���뵽ha[adr]�ĵ�������//������ظ�ֵ
		ha[adr].firstp = q;
	}
	n++;						//����ܸ�����1
}

//mΪ��ϣ�����鳤�ȣ�nΪ��ϣ����ЧԪ�ظ�����n1Ϊԭʼ��Ϣ���鳤��
void CreateHT(HashTable ha[], int& n, int m, KeyType keys[], int n1)  //������ϣ��
{
	for (int i = 0; i < m; i++)			//��ϣ���ó�ֵ
		ha[i].firstp = NULL;
	n = 0;
	for (int i = 0; i < n1; i++)
		InsertHT(ha, n, m, keys[i]);//����n���ؼ���
}

void SearchHT(HashTable ha[], int m, KeyType k)	//�ڹ�ϣ���в��ҹؼ���k
{
	int cnt = 0, adr;
	adr = k % m;					//�����ϣ����ֵ
	NodeType* q;
	q = ha[adr].firstp;			//qָ���Ӧ��������׽��
	while (q != NULL)				//ɨ�赥����adr�����н��
	{
		cnt++;
		if (q->key == k)			//���ҳɹ�
			break;				//�˳�ѭ��
		q = q->next;
	}
	if (q != NULL)				//���ҳɹ�
		printf("�ɹ����ؼ���%d���Ƚ�%d��\n", k, cnt);
	else						//����ʧ��
		printf("ʧ�ܣ��ؼ���%d���Ƚ�%d��\n", k, cnt);
}


bool DeleteHT(HashTable ha[], int& n, int m, KeyType k)	//ɾ����ϣ���йؼ���k
{
	int adr;
	adr = k % m;					//�����ϣ����ֵ
	NodeType* q, * preq;
	q = ha[adr].firstp;			//qָ���Ӧ��������׽��
	if (q == NULL)
		return false;			//��Ӧ������Ϊ��
	if (q->key == k)				//�׽����ڣ���Ϊk��ɾ���׽��
	{
		ha[adr].firstp = q->next;//ɾ�����q
		free(q);
		n--;					//����ܸ�����1
		return true;			//������
	}
	preq = q; q = q->next;			//�׽����ڣ���Ϊkʱ�����β鿴������㣬�鵽��ɾ��
	while (q != NULL && q->key != k)//����
	{
		preq = q;
		q = q->next;
	}
	if (q != NULL)				//���ҳɹ�
	{
		preq->next = q->next;		//ɾ�����q
		free(q);
		n--;					//����ܸ�����1
		return true;			//������
	}
	else return false;			//δ�ҵ�k,���ؼ�
}

void ASL(HashTable ha[], int n, int m)	//��ƽ�����ҳ���
{
	int succ = 0, unsucc = 0, s;
	NodeType* q;
	for (int i = 0; i < m; i++)		//ɨ�����й�ϣ���ַ�ռ�
	{
		s = 0;
		q = ha[i].firstp;			//qָ������i���׽��
		while (q != NULL)			//ɨ�赥����i�����н��
		{
			q = q->next;
			s++;				//s��¼��ǰ����Ƕ�Ӧ������ĵڼ������
			succ += s;			//�ۼƳɹ����ܱȽϴ���
		}
		unsucc += s;				//�ۼƲ��ɹ����ܱȽϴ���
	}
	printf(" �ɹ������ASL(%d)=%g\n", n, succ * 1.0 / n);  //nΪ�ؼ��ָ���
	printf(" ���ɹ������ASL(%d)=%g\n", n, unsucc * 1.0 / m);    //mΪ��ϣ����
}

void DispHT(HashTable ha[], int n, int m)  //�����ϣ��
{
	int succ = 0, unsucc = 0, s;
	NodeType* q;
	for (int i = 0; i < m; i++)		//ɨ�����й�ϣ���ַ�ռ�
	{
		s = 0;
		printf(" %3d:\t", i);
		q = ha[i].firstp;			//qָ������i���׽��
		while (q != NULL)			//ɨ�赥����i�����н��
		{
			printf("%4d", q->key);
			q = q->next;
			s++;				//s��¼��ǰ����Ƕ�Ӧ������ĵڼ������
			succ += s;			//�ۼƳɹ����ܱȽϴ���
		}
		unsucc += s;				//�ۼƲ��ɹ����ܱȽϴ���
		printf("\n");
	}
	printf(" �ɹ������ASL(%d)=%g\n", n, succ * 1.0 / n);
	printf(" ���ɹ������ASL(%d)=%g\n", n, unsucc * 1.0 / m);
}

void DestroyHT(HashTable ha[], int m)	//���ٹ�ϣ��
{
	int i;
	NodeType* q, * preq;
	for (i = 0; i < m; i++)
	{
		q = ha[i].firstp;			//qָ������i���׽��
		while (q != NULL)			//ɨ�赥����i�����н��
		{
			preq = q; q = q->next;
			free(preq);
		}
	}
}
