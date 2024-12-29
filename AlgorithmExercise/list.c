#define _CRT_SECURE_NO_WARNINGS 1

#include"list.h"

//˫������ʼ������ʼ����ͷ�ڵ�OK
//˫����Ҫ����дInit������ԭ����������صĽṹ������ͷ�ڵ���ѭ��
ListNode* ListInit()
{
    ListNode* plist = ListCreatNode(" ");

    //һ��ע���봴��ͨ��㲻ͬ��������˫����ͷ�ڵ㣬һ����ѭ��
    plist->next = plist;
    plist->prev = plist;

    return plist;
}

// ����һ��˫�����Ľ�㲢���ص�ַ.˳����ʼ��val OK
//ListNode* ListCreatNode()����ʼ��val
ListNode* ListCreatNode(const LTDataType x)
{
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL)
    {
        perror("malloc fail");
        exit(-1); //ע�⺯������ֵ����ListNode* ����return
    }
    if (x == " ") return newNode;
    strncpy(newNode->val, x, 4);
    newNode->val[4] = '\0'; // ȷ���ַ�����ֹ��
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}
// ˫����������
void ListDestory(ListNode* plist)
{
    assert(plist);

    ListNode* cur = plist->next;
    while (cur != plist)
    {
        ListNode* curNext = cur->next;
        free(cur);
        plist->next = curNext;
        curNext->prev = plist;
        cur = curNext;

        //��ʵ���������ӽ��
        // ListNode* next = cur->next;
        // free(cur);
        // cur = next;
    }
    cur = NULL;
    free(plist);
    plist = NULL;

    printf("List have been destoried\n");
}

// ˫��������ӡOK
void ListPrint(ListNode* plist)
{
    assert(plist);

    //printf("head<=>");

    ListNode* cur = plist->next; //��Ϊ��˫��������Ч���Ϊ plist->next
    while (cur != plist) //while(cur)ע������˫��������û�пյ�ʱ��
    {
        printf("%s", cur->val);
        cur = cur->next;
    }
    printf("\n");
}

// ˫������β��
void ListPushBack(ListNode* plist, LTDataType x)
{
    assert(plist);

    ListNode* newNode = ListCreatNode(x);
    ListNode* tail = plist->prev;

    //������û����Ч��㶼����
    // phead            tail  newnode
    tail->next = newNode;
    newNode->prev = tail;
    newNode->next = plist;
    plist->prev = newNode;
}
// ˫������ͷ��ok
void ListPushFront(ListNode* plist, LTDataType x)
{
    assert(plist);

    ListNode* newNode = ListCreatNode(x);

    newNode->next = plist->next;
    plist->next->prev = newNode;
    plist->next = newNode;
    newNode->prev = plist;

    //ListInsert(plist->next, x);
}