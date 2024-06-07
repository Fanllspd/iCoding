#include <stdio.h>
#include <stdlib.h>
#include "list.h" // 请不要删除，否则检查不通过

/**
 * 链表 删除范围内结点

已知线性表中的元素（整数）以值递增有序排列，并以单链表作存储结构。试写一高效算法，删除表中所有大于mink且小于maxk的元素（若表中存在这样的元素），分析你的算法的时间复杂度。

链表结点定义如下：
struct _lnklist{
    ElemType data;
    struct _lnklist *next;
};
typedef struct _lnklist Node;
typedef struct _lnklist *LinkList;
函数原型如下：
void lnk_del_x2y(LinkList L, ElemType mink, ElemType maxk)

其中L指向链表的头结点。
*/

// O(N^2)
void lnk_del_x2y(LinkList L, int mink, int maxk)
{
    while (1)
    {
        Node *pL = L, *temp = L->next;
        while (pL->next)
        {
            if (pL->next->data >= maxk)
                return;
            if (pL->next->data > mink)
            {
                pL->next = temp->next;
                free(temp);
                break;
            }
            pL = pL->next;
            temp = temp->next;
        }
    }
}

// O(N)
void lnk_del_x2y2(LinkList L, int mink, int maxk)
{
    Node *pL = L, *temp = L->next;
    while (pL->next && pL->next->data <= mink)
    {
        pL = pL->next;
    }

    temp = pL->next;
    while (pL->next && pL->next->data < maxk)
    {
        pL->next = temp->next;
        free(temp);
        temp = pL->next;
        // break;
    }
}

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

int main(int argc, char const *argv[])
{
    LinkList A = (LinkList)malloc(sizeof(LinkList));
    A->next = NULL;
    int nums1[] = {1, 2, 3, 4, 5, 6};
    create_node(&A, nums1, sizeof(nums1) / sizeof(nums1[0]));
    lnk_del_x2y2(A, 3, 6);
    return 0;
}
