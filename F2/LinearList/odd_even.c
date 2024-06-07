#include <stdio.h>
#include <stdlib.h>
#include "list.h" // 请不要删除，否则检查不通过
/**
 * 顺序表 数据调整

    已知顺序表L中的数据元素类型为int。设计算法将其调整为左右两部分，
    左边的元素（即排在前面的）均为奇数，右边所有元素（即排在后面的）均为偶数，
    并要求算法的时间复杂度为O(n),
    空间复杂度为O（1）。

    函数原型如下：
    void odd_even(SeqList *L);

    相关定义如下：
    struct _seqlist{
        ElemType elem[MAXSIZE];
        int last;
    };
    typedef struct _seqlist SeqList;
*/

void odd_even(SeqList *L)
{
    int left = 0,
        right = L->last,
        temp = 0;

    while (left < right)
    {

        if (L->elem[left] % 2 == 0 && L->elem[right] % 2 != 0)
        {
            temp = L->elem[right];
            L->elem[right] = L->elem[left];
            L->elem[left] = temp;
            right--;
            left++;
        }
        if (L->elem[left] % 2 != 0)
            left++;

        if (L->elem[right] % 2 == 0)
            right--;
    }
}

int main(int argc, char const *argv[])
{
    SeqList A;
    A.last = -1;
    int arr[] = {511, 528, 267, 23, 900, 475, 890, 618, 669, 214, 916, 781, 400, 341, 168, 233, 809, 298, 36, 315, 273, 647, 105, 431};
    for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
    {
        A.elem[++A.last] = arr[i];
    }
    odd_even(&A);
    return 0;
}
