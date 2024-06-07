#include <stdio.h>
#include <stdlib.h>
#include "list.h" // 请不要删除，否则检查不通过

/*
    队列 循环链表表示队列

        假设以带头结点的循环链表表示队列，并且只设一个指针指向队尾元素结点（注意不设头指针），请完成下列任务：

    1 : 队列初始化，成功返回真，否则返回假： bool init_queue(LinkQueue *LQ);

    2 : 入队列，成功返回真，否则返回假： bool enter_queue(LinkQueue *LQ, ElemType x);

    3 : 出队列，成功返回真，且 *x为出队的值，否则返回假 bool leave_queue(LinkQueue *LQ, ElemType *x);

    相关定义如下：

    typedef struct _QueueNode
    {
        ElemType data;           // 数据域
        struct _QueueNode *next; // 指针域
    } LinkQueueNode, *LinkQueue;
*/

typedef int ElemType;

bool init_queue(LinkQueue *LQ)
{
    *LQ = (LinkQueue)malloc(sizeof(LinkQueueNode));
    if (!LQ)
        return false;
    // (*LQ)->data = NULL;
    (*LQ)->next = *LQ;
    return true;
}

bool enter_queue(LinkQueue *LQ, ElemType x)
{
    LinkQueueNode *newQueueNode = (LinkQueueNode *)malloc(sizeof(LinkQueueNode));
    if (!newQueueNode)
        return false;
    newQueueNode->data = x;
    newQueueNode->next = (*LQ)->next;
    (*LQ)->next = newQueueNode;
    (*LQ) = (*LQ)->next;
    return true;
}

bool leave_queue(LinkQueue *LQ, ElemType *x)
{
    if ((*LQ)->next == *LQ)
        return false;

    LinkQueueNode *firstNode = (*LQ)->next->next;
    *x = firstNode->data;
    (*LQ)->next->next = firstNode->next;
    if (firstNode == *LQ) // 如果为最后一个
        *LQ = (*LQ)->next;
    free(firstNode);
    return true;
}

int main(int argc, char const *argv[])
{
    LinkQueue linkQueue;
    init_queue(&linkQueue);
    enter_queue(&linkQueue, 1);
    enter_queue(&linkQueue, 2);
    enter_queue(&linkQueue, 3);
    enter_queue(&linkQueue, 4);
    int x, y, z, a;
    leave_queue(&linkQueue, &x);
    leave_queue(&linkQueue, &y);
    leave_queue(&linkQueue, &z);
    leave_queue(&linkQueue, &a);
    // enter_queue(&linkQueue, 5);

    // enter_queue(&linkQueue, 5);
    // enter_queue(&linkQueue, 6);
    // enter_queue(&linkQueue, 7);
    // enter_queue(&linkQueue, 8);
    // leave_queue(&linkQueue, &x);
    // leave_queue(&linkQueue, &y);
    // leave_queue(&linkQueue, &z);
    // leave_queue(&linkQueue, &a);

    return 0;
}
