#include <stdio.h>
#include <stdlib.h>
#include "list.h" // 请不要删除，否则检查不通过

/**
 * 顺序表 删除指定范围

    设计一个高效的算法，从顺序表L中删除所有值介于x和y之间(包括x和y) 的所有元素（假设y
    >= x），要求时间复杂度为O(n)，空间复杂度为O(1)。

    函数原型如下：
    void del_x2y(SeqList *L, ElemType x, ElemType y);

    相关定义如下：
    struct _seqlist
    {
        ElemType elem[MAXSIZE];
        int last;
    };
    typedef struct _seqlist SeqList;
*/

void del_x2y(SeqList *L, int x, int y)
{
    int i = 0;
    for (int j = 0; j < L->last + 1; j++)
    {
        if (L->elem[j] < x || L->elem[j] > y)
        {
            L->elem[i++] = L->elem[j];
        }
    }
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
    del_x2y(&A, 188, 193);
    return 0;
}
