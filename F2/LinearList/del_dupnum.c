#include <stdio.h>
#include <stdlib.h>
#include "list.h" // 请不要删除，否则检查不通过
/**
 * 顺序表 删除重复

    编写算法，在一非递减的顺序表L中，删除所有值相等的多余元素。要求时间复杂度为O(n)，空间复杂度为O(1)。

    函数原型如下：
    void del_dupnum(SeqList *L)

    相关定义如下：
    struct _seqlist
    {
        ElemType elem[MAXSIZE];
        int last;
    };
    typedef struct _seqlist SeqList;
*/

void del_dupnum(SeqList *L)
{
    int map[1001] = {0},
        i = 0;
    // SeqList newList;
    // newList.last = -1;
    for (int j = 0; j < L->last + 1; j++)
    {
        if (map[L->elem[j]] == 0)
        {
            map[L->elem[j]] = 1;
            // newList.elem[++newList.last] = L->elem[j];
            L->elem[i++] = L->elem[j];
        }
    }
    // *L = newList;
    L->last = i - 1;
}

int main(int argc, char const *argv[])
{
    SeqList A;
    A.last = -1;
    int arr[] = {182, 187, 188, 193, 193, 195, 198};
    for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
    {
        A.elem[++A.last] = arr[i];
    }
    del_dupnum(&A);
    return 0;
}
