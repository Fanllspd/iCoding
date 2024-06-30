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

void pre_order(BiTree root)
{
    if (root == NULL)
        return;
    Stack s;
    init_stack(&s);
    BiTree current = root;
    push(&s, current);

    while (!is_empty(&s))
    {
        // BiTree node = (BiTree)malloc(sizeof(BiTree));
        // top(&s, &node);
        pop(&s, &current);
        visit_node(current);

        if (current->right)
            push(&s, current->right);
        if (current->left)
            push(&s, current->left);
    }
}

BiTNode *createNode(DataType data)
{
    BiTNode *newNode = (BiTNode *)malloc(sizeof(BiTNode));
    if (newNode != NULL)
    {
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

int main(int argc, char const *argv[])
{
    BiTNode *root = createNode(0);
    root->left = createNode(0);
    root->right = createNode(0);
    root->left->left = createNode(0);
    root->left->right = createNode(0);
    root->right->left = createNode(0);
    root->right->right = createNode(0);

    pre_order(root);
    return 0;
}
