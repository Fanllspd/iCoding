#include <stdlib.h>
#include <stdio.h>
#include "bitree.h" //请不要删除，否则检查不通过

void init_stack(Stack *S)
{
    S->top = -1;
}

bool push(Stack *S, ElemType x)
{
    if (S->top >= Stack_Size - 1)
    {
        return false; // Stack is full
    }
    S->elem[++(S->top)] = x;
    return true;
}

bool pop(Stack *S, ElemType *px)
{
    if (S->top == -1)
    {
        return false; // Stack is empty
    }
    *px = S->elem[(S->top)--];
    return true;
}

bool top(Stack *S, ElemType *px)
{
    if (S->top == -1)
    {
        return false; // Stack is empty
    }
    *px = S->elem[S->top];
    return true;
}

bool is_empty(Stack *S)
{
    return S->top == -1;
}

bool path(BiTNode *root, BiTNode *node, Stack *s)
{
    if (root == NULL || node == NULL)
        return false;

    push(s, root);

    if (root == node)
        return true;

    if (path(root->left, node, s) || path(root->right, node, s))
        return true;

    pop(s, &(s->elem[s->top]));
    return false;
}

int main(int argc, char const *argv[])
{
    BiTNode node6 = {6, NULL, NULL};
    BiTNode node7 = {7, NULL, NULL};
    BiTNode node4 = {4, NULL, NULL};
    BiTNode node2 = {2, &node7, &node4};
    BiTNode node5 = {5, &node6, &node2};
    BiTNode node0 = {0, NULL, NULL};
    BiTNode node8 = {8, NULL, NULL};
    BiTNode node1 = {1, &node0, &node8};
    BiTNode node3 = {3, &node5, &node1};

    BiTNode *root = &node3;
    BiTNode *p = &node7;
    Stack sPath;
    init_stack(&sPath);

    BiTNode *q = &node7;
    bool lca = path(root, p, &sPath);
    if (lca)
    {
        while (!is_empty(&sPath))
        {
            int *a;
            pop(&sPath, &a);
            printf("%d ", *a);
        }
    }
    else
    {
        printf("未找到路径\n");
    }
    return 0;
}
