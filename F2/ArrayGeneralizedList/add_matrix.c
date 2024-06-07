#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tsmatrix.h"

bool add_matrix(const TSMatrix *pM, const TSMatrix *pN, TSMatrix *pQ)
{
    if ((pM->m != pN->m) || pM->n != pN->n)
        return false;
    pQ->m = pM->m;
    pQ->n = pM->n;
    pQ->len = 0;

    int i = 0, j = 0, k = 0;

    while (i < pM->len && j < pN->len)
    {
        if ((pM->data[i].i < pN->data[j].i) || (pM->data[i].i == pN->data[j].i && pM->data[i].j < pN->data[j].j))
            pQ->data[k++] = pM->data[i++];

        else if ((pM->data[i].i > pN->data[j].i) || (pM->data[i].i == pN->data[j].i && pM->data[i].j > pN->data[j].j))
            pQ->data[k++] = pN->data[j++];

        else
        {
            pQ->data[k] = pM->data[i];
            pQ->data[k].e = pM->data[i].e + pN->data[j].e;
            if (pQ->data[k].e)
                k++;
            i++;
            j++;
        }
    }

    while (i < pM->len)
        pQ->data[k++] = pM->data[i++];

    while (j < pN->len)
        pQ->data[k++] = pN->data[j++];

    pQ->len = k;
    return true;
}

void printSparseMatrix(TSMatrix *matrix)
{
    for (int i = 0; i < matrix->len; i++)
    {
        printf("(%d, %d, %d)\n", matrix->data[i].i, matrix->data[i].j, matrix->data[i].e);
    }
}

int main()
{
    // 定义两个稀疏矩阵 M 和 N
    TSMatrix M = {{{1, 4, 24},
                   {2, 3, 2}},
                  2,
                  4,
                  2};
    TSMatrix N = {{{1, 1, 17}},
                  2,
                  4,
                  1};

    // 定义结果矩阵 Q
    TSMatrix Q;

    // 执行稀疏矩阵加法
    add_matrix(&M, &N, &Q);

    // 打印结果矩阵
    printf("Resultant Sparse Matrix C:\n");
    printSparseMatrix(&Q);

    return 0;
}