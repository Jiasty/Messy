#define _CRT_SECURE_NO_WARNINGS 1

#include"list.h"

//双链表初始化，初始化出头节点OK
//双链表要单独写Init函数的原因就是它独特的结构，带有头节点且循环
ListNode* ListInit()
{
    ListNode* plist = ListCreatNode(" ");

    //一定注意与创普通结点不同，这里是双链表头节点，一定得循环
    plist->next = plist;
    plist->prev = plist;
    plist->NodeNum = 0;
    return plist;
}

// 创建一个双链表的结点并返回地址.顺带初始化val OK
//ListNode* ListCreatNode()不初始化val
ListNode* ListCreatNode(const LTDataType x)
{
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL)
    {
        perror("malloc fail");
        exit(-1); //注意函数返回值类型ListNode* 别用return
    }
    if (strcmp(x, " ") == 0) return newNode;
    // 为字符串分配内存并复制内容
    // 由于val的类型为typedef char* LTDataType，不是一个固定长度的字符数组
    // 因此每次插入一个新的节点时，你需要为该字符串分配内存。
    // 如果直接将 temp 赋值给 val，而不分配内存，那么会遇到悬挂指针的问题。
    newNode->val = (char*)malloc(strlen(x) + 1); //此处很重要！！！
    if (newNode->val == NULL) 
    {
        perror("malloc failed for string");
        exit(-1);
    }
    strncpy(newNode->val, x, strlen(x) + 1);
    newNode->val[strlen(x) + 1] = '\0'; // 确保字符串终止符
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}
// 双向链表销毁
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
    }
    cur = NULL;
    free(plist);
    plist = NULL;
}

// 双向链表打印OK
void ListPrint(ListNode* plist)
{
    assert(plist);

    //printf("head<=>");

    ListNode* cur = plist->next; //因为是双链表，有效结点为 plist->next
    while (cur != plist) //while(cur)注意这是双向链表，没有空的时候
    {
        printf("%s", cur->val);
        if (cur->next != plist) printf(",");
        cur = cur->next;
    }
    printf("\n");
}

// 双向链表尾插
void ListPushBack(ListNode* plist, LTDataType x)
{
    assert(plist);

    ListNode* newNode = ListCreatNode(x);
    newNode->NodeNum++;
    ListNode* tail = plist->prev;

    //不管有没有有效结点都适用
    // phead            tail  newnode
    tail->next = newNode;
    newNode->prev = tail;
    newNode->next = plist;
    plist->prev = newNode;
}
// 双向链表头插ok
void ListPushFront(ListNode* plist, LTDataType x)
{
    assert(plist);

    ListNode* newNode = ListCreatNode(x);
    newNode->NodeNum++;

    newNode->next = plist->next;
    plist->next->prev = newNode;
    plist->next = newNode;
    newNode->prev = plist;

    //ListInsert(plist->next, x);
}

int NodeNum(ListNode* plist)
{
    return plist->NodeNum;
}