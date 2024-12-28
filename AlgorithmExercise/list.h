#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

//��ͷ+˫��+ѭ������
typedef char* LTDataType;

typedef struct ListNode
{
    LTDataType val;
    struct ListNode* next;
    struct ListNode* prev;
}ListNode;

//˫�����ʼ������ʼ����ͷ�ڵ�
ListNode* ListInit();

// ����һ��˫����Ľ�㲢���ص�ַ.˳����ʼ��val
ListNode* ListCreatNode(const LTDataType x);
// ˫����������
void ListDestory(ListNode* plist);

// ˫�������ӡ
void ListPrint(ListNode* plist);

// ˫������β��
void ListPushBack(ListNode* plist, LTDataType x);
// ˫������ͷ��
void ListPushFront(ListNode* plist, LTDataType x);