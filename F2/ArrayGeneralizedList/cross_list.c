#include <stdio.h>
#include <stdlib.h>
#include "crosslist.h"

int init_cross_list(PCrossList L, const ElemType *A, int m, int n)
{
    L->rows = m;
    L->cols = n;
    L->nums = 0;
    L->rowhead = (OLink *)calloc(m, sizeof(OLink));
    L->colhead = (OLink *)calloc(n, sizeof(OLink));

    OLNode *rowPtr = NULL,
           *colPtr = NULL;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // A[i*n+j]
            if (A[i * n + j] != 0)
            {
                OLNode *olNode = (OLNode *)malloc(sizeof(OLNode));
                if (olNode == NULL)
                    return -1;
                olNode->row = i + 1;
                olNode->col = j + 1;
                olNode->value = A[i * n + j];
                olNode->right = NULL;
                olNode->down = NULL;

                if (L->rowhead[i] == NULL)
                {
                    olNode->right = L->rowhead[i];
                    L->rowhead[i] = olNode;
                }
                else
                {
                    rowPtr = L->rowhead[i];
                    while (rowPtr->right)
                        rowPtr = rowPtr->right;
                    olNode->right = NULL;
                    rowPtr->right = olNode;
                }

                if (L->colhead[j] == NULL)
                {
                    olNode->down = L->colhead[j];
                    L->colhead[j] = olNode;
                }
                else
                {
                    colPtr = L->colhead[j];
                    while (colPtr->down)
                        colPtr = colPtr->down;
                    olNode->down = NULL;
                    colPtr->down = olNode;
                }

                L->nums++;
            }
        }
    }
    return L->nums;
}

int del_cross_list(PCrossList L, ElemType k)
{
    OLNode *temp = NULL, *prev = NULL;

    int delCnt = 0;
    for (int i = 0; i < L->rows; i++)
    {
        prev = NULL;
        OLNode *rowPtr = L->rowhead[i];
        while (rowPtr)
        {
            if (rowPtr->value == k)
            {
                if (prev == NULL)
                    L->rowhead[i] = rowPtr->right;
                else
                    prev->right = rowPtr->right;

                rowPtr = rowPtr->right;
            }
            else
            {
                prev = rowPtr;
                rowPtr = rowPtr->right;
            }
        }
    }

    for (int i = 0; i < L->cols; i++)
    {
        prev = NULL;
        OLNode *colPtr = L->colhead[i];
        while (colPtr)
        {
            if (colPtr->value == k)
            {
                if (prev == NULL)
                    L->colhead[i] = colPtr->down;
                else
                    prev->down = colPtr->down;
                temp = colPtr;
                colPtr = colPtr->down;
                free(temp);
                L->nums--;
                delCnt++;
            }
            else
            {
                prev = colPtr;
                colPtr = colPtr->down;
            }
        }
    }

    return delCnt;
}

void print_cross_list_triplet(PCrossList L)
{
    printf("Row\tCol\tValue\n");
    for (int i = 0; i < L->rows; i++)
    {
        OLNode *rowPtr = L->rowhead[i];
        while (rowPtr != NULL)
        {
            printf("%d\t%d\t%d\n", rowPtr->row, rowPtr->col, rowPtr->value);
            rowPtr = rowPtr->right;
        }
    }
}

void free_cross_list(PCrossList L)
{
    for (int i = 0; i < L->rows; i++)
    {
        OLNode *current = L->rowhead[i];
        while (current != NULL)
        {
            OLNode *temp = current;
            current = current->right;
            free(temp);
        }
    }
    free(L->rowhead);
    for (int j = 0; j < L->cols; j++)
    {
        OLNode *current = L->rowhead[j];
        while (current != NULL)
        {
            OLNode *temp = current;
            current = current->down;
            free(temp);
        }
    }
    free(L->rowhead);
    free(L);
}

int main()
{
    int m = 6; // number of rows
    int n = 2; // number of columns
    ElemType A[] = {
        1, 91,
        2, 53,
        3, 4,
        0, 98,
        0, 0,
        0, 14}; // sample input array

    CrossList L;
    L.rowhead = (OLink *)calloc(m, sizeof(OLink));
    L.colhead = (OLink *)calloc(n, sizeof(OLink));
    L.rows = m;
    L.cols = n;
    L.nums = init_cross_list(&L, A, m, n);

    printf("Non-zero elements in the cross list: %d\n", L.nums);

    // Print the cross list for verification
    printf("Printing the cross list:\n");
    print_cross_list_triplet(&L);

    printf("DelCnt: %d\n", del_cross_list(&L, 1));
    print_cross_list_triplet(&L);
    // free_cross_list(&L);

    return 0;
}