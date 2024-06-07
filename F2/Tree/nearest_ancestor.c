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

void visit_node(BiTNode *node)
{
    node->data = 1;
    return;
}

bool path(BiTNode *root, BiTNode *node, Stack *s)
{
    if (root == NULL)
    {
        return false;
    }
    push(s, root); // 将当前节点压入栈中

    if (root == node)
    { // 如果当前节点是目标节点
        return true;
    }

    // 递归查找左子树或右子树
    if ((root->left && path(root->left, node, s)) || (root->right && path(root->right, node, s)))
    {
        return true;
    }

    // 如果当前节点不在路径上，则将其从栈中弹出
    pop(s, &(s->elem[s->top]));
    return false;
}

void swap(Stack *p, Stack *q)
{
    Stack tmp = *p;
    *p = *q;
    *q = tmp;
}

BiTNode *nearest_ancestor(BiTree root, BiTNode *p, BiTNode *q)
{
    Stack sP, sQ;

    init_stack(&sP);
    init_stack(&sQ);

    if (!path(root, p, &sP) || !path(root, q, &sQ))
        return NULL;

    if (sP.top < sQ.top)
        swap(&sP, &sQ);

    BiTree nodeP, nodeQ;
    while (sP.top != sQ.top)
        pop(&sP, &nodeP);

    while (!is_empty(&sP) && !is_empty(&sQ))
    {
        pop(&sP, &nodeP);
        pop(&sQ, &nodeQ);
        if (nodeP == nodeQ)
            return nodeP;
    }
    return NULL;
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
    BiTNode *p = &node5;
    BiTNode *q = &node7;
    BiTNode *lca = nearest_ancestor(root, p, q);
    if (lca)
    {
        printf("节点 %d 和节点 %d 的最近公共祖先是节点 %d\n", p->data, q->data, lca->data);
    }
    else
    {
        printf("未找到最近公共祖先\n");
    }
    return 0;
}
