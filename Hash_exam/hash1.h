#pragma once
#include <stdio.h>
#include <stdlib.h>

#define MaxSize 100			//��������ϣ����
#define NULLKEY -1  //��ʾΪ��
typedef int KeyType;

typedef struct HashTable
{
    KeyType key;
    int count; //̽�����
} HashTable;

void InsertHT(HashTable ha[], int& n, int m, int p, KeyType k)  //���ؼ���k���뵽��ϣ����
{
    int cnt, adr;
    if (n == m)	return;//��ռ��ѱ�ռ��

    adr = k % p;					//�����ϣ����ֵ
    if (ha[adr].key == NULLKEY)	//k����ֱ�ӷ��ڹ�ϣ����
    {
        ha[adr].key = k;
        ha[adr].count = 1;
    }
    else						//������ͻʱ��������̽�ⷨ�����ͻ
    {
        cnt = 1;					//cnt��¼k������ͻ�Ĵ���
        while (ha[adr].key != NULLKEY && ha[adr].key != k)//��ֹ�ظ�������ͬ�ؼ��֡��̲���ûд��
        {
            adr = (adr + 1) % m;	//����̽��
            cnt++;
        }

        if (ha[adr].key == k)	 return;//�ظ�������ͬ�ؼ��֡��̲���ûд��

        ha[adr].key = k;			//��adr������k
        ha[adr].count = cnt;		//����̽�����
    }
    n++;						//�ܹؼ��ָ�����1
}
// ��ʼ����ϣ��
void CreateHT(HashTable ha[], int& n, int m, int p, KeyType keys[], int total)
{
    for (int i = 0; i < m; i++)				//��ϣ���ÿյĳ�ֵ
    {
        ha[i].key = NULLKEY;
        ha[i].count = 0;
    }
    n = 0;
    for (int i = 0; i < total; i++)
        InsertHT(ha, n, m, p, keys[i]);		//����n���ؼ���
}

// ��ϣ����
int hashFunction(int key, int p)
{
    return key % p;
}



// ����Ԫ��
void SearchHT(HashTable ha[], int m, int p, KeyType k)  //�ڹ�ϣ���в��ҹؼ���k
{
    int cnt = 1, adr;
    adr = k % p;					//�����ϣ����ֵ
    while (ha[adr].key != NULLKEY && ha[adr].key != k && cnt < m)
    {
        cnt++;					//�ۼƹؼ��ֱȽϴ���
        adr = (adr + 1) % m;		//����̽��
    }
    if (ha[adr].key == k)			//���ҳɹ�
        printf("�ɹ����ؼ���%d���Ƚ�%d��\n", k, cnt);
    else						//����ʧ��
        printf("ʧ�ܣ��ؼ���%d���Ƚ�%d��\n", k, cnt);
}

// ɾ��Ԫ��
bool DeleteHT(HashTable ha[], int& n, int m, int p, KeyType k)	//ɾ����ϣ���йؼ���k
{
    int cnt = 1, adr;
    adr = k % p;					//�����ϣ����ֵ
    while (ha[adr].key != NULLKEY && ha[adr].key != k && cnt < m)
    {
        cnt++;					//�ۼƹؼ��ֱȽϴ���
        adr = (adr + 1) % m;		//����̽��
    }

    if (ha[adr].key == k)			//���ҳɹ�
    {
        ha[adr].key = NULLKEY;						//ɾ���ҵ��ĸô�
        ha[adr].count = 0;
        n--;											//��ϣ����Ԫ�ظ�������1

        int last_empty = adr;//��ס������λ�ã���һ����Ѩo
        int probe = (adr + 1) % m;   //probeΪ��һ�����ܴ�����̽adr�ĺ��ͬ��ʴ���ɾ��Ԫ��λ��#
        while (ha[probe].key != NULLKEY)//һֱ������λ����˵�����λ��û��Ҫ����������ˡ�
        {									//����ɾ����һ��Ԫ�أ������ҵ���λ��������ѭ���������ˡ�
            int ideal = ha[probe].key % p; //���Ԫ�ر�����ڵ�λ��v�������ǳ�ͻ������� 	
            if ((ideal <= last_empty && last_empty < probe) ||    //--v=o��=�����ظ���#
                (probe < ideal && ideal <= last_empty) || //����probe==ideal��˵���ǡ���λ�������ݲ�
                (last_empty < probe && probe < ideal)) //--o#
            {
                ha[last_empty].key = ha[probe].key;	//��ͬ�����ǰ�ƶ������Ͽ�Ѩ

                ha[last_empty].count = (ha[probe].count - (probe - last_empty)) % m;
                //�����Ѩ������λ�ã���ô���Ĳ��ҵĴ���countӦ�÷����仯��
                //��Ϊ���Ƶ���Ѩ���൱��ǰ���ˣ�����count���С

                ha[probe].key = NULLKEY;//�γ��¿�Ѩ		
                last_empty = probe;//��ָ���¿�Ѩ

            }
            probe = (probe + 1) % m;       //������̽ѭ�����λ�� 
        }
        return true;						//���ҳɹ�����true 
    }
    else												//����ʧ�ܵ���� 
        return false;									//����false
}

void DispHT(HashTable ha[], int n, int m, int p)  //�����ϣ��
{
    int i, j;
    int succ = 0, unsucc = 0, s;
    printf("��ϣ��:\n");
    printf(" ��ϣ���ַ:\t");
    for (i = 0; i < m; i++)
        printf(" %3d", i);
    printf(" \n");
    printf(" ��ϣ��ؼ���:\t");
    for (i = 0; i < m; i++)
        if (ha[i].key == NULLKEY)
            printf("    ");			//���3���ո�
        else
            printf(" %3d", ha[i].key);
    printf(" \n");
    printf(" ̽�����:\t");
    for (i = 0; i < m; i++)
        if (ha[i].key == NULLKEY)
            printf("    ");			//���3���ո�
        else
            printf(" %3d", ha[i].count);
    printf(" \n");
}