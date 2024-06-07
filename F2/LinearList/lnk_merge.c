/**
 *
 * 链表 合并

设线性表A=(a1, a2,…,am)，B=(b1, b2,…,bn)，试写一个按下列规则合并A、B为线性表C的算法，使得：
C= (a1, b1,…,am, bm, bm+1, …,bn) 当m≤n时；
或者
C= (a1, b1,…,an, bn, an+1, …,am) 当m>n时。
线性表A、B、C均以单链表作为存储结构，且C表利用A表和B表中的结点空间构成。注意：单链表的长度值m和n均未显式存储。
函数的原型如下：
void lnk_merge(LinkList A, LinkList B, LinkList C)
即将A和B合并为C，其中 C 已经被初始化为空单链表
相关定义如下：

struct _lnklist{
    ElemType data;
    struct _lnklist *next;
};

typedef struct _lnklist Node;
typedef struct _lnklist *LinkList;
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h" // 请不要删除，否则检查不通过

void create_node(LinkList *linkList, int nums[], int len)
{
    Node *node = *linkList;
    int i = 0;
    for (int i = 0; i < len; i++)
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = nums[i];
        node->next = newNode;
        node = node->next;
    }

    node->next = NULL;
}

void lnk_merge(LinkList A, LinkList B, LinkList C)
{
    Node *pA = A->next, *pB = B->next, *pC = C;
    // int counts = 0;
    while (pA && pB)
    {
        // pC->next = (Node *)malloc(sizeof(Node));

        pC->next = pA;
        pA = pA->next;
        pC = pC->next;

        pC->next = pB;
        pB = pB->next;
        pC = pC->next;
        // counts += 2;
    }
    while (pA)
    {
        pC->next = pA;
        pC = pC->next;
        pA = pA->next;
        // counts++;
    }
    while (pB)
    {
        pC->next = pB;
        pC = pC->next;
        pB = pB->next;
        // counts++;
    }
    // printf("%d", counts);
    pC->next = NULL;
}
int main(int argc, char const *argv[])
{
    LinkList A = (LinkList)malloc(sizeof(LinkList)),
             B = (LinkList)malloc(sizeof(LinkList)),
             C = (LinkList)malloc(sizeof(LinkList));
    A->next = NULL;
    int nums1[] = {7, 27, 22, 20, 57, 2, 28, 2, 10, 50, 52, 12, 29, 52, 23, 35, 6, 33, 20, 52, 20, 12, 15, 37, 38, 39};
    create_node(&A, nums1, sizeof(nums1) / sizeof(nums1[0]));

    B->next = NULL;
    int nums2[] = {30, 14, 32, 39, 9, 31, 6, 31, 52, 4, 34, 12, 58};
    create_node(&B, nums2, sizeof(nums2) / sizeof(nums2[0]));
    // strncpy(C->data, "C1", 2);
    // C->next = (LinkList)malloc(sizeof(Node));
    // strncpy(C->next->data, "C2", 2);
    C->next = NULL;
    // C->data = NULL;
    lnk_merge(A, B, C);
    return 0;
}
