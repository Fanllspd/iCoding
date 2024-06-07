#include <stdlib.h>
#include <stdio.h>
#include "bitree.h" //请不要删除，否则检查不通过

// 创建队列
Queue *create_queue()
{
    Queue *newQueue = (Queue *)malloc(sizeof(Queue));
    if (!newQueue)
    {
        return NULL;
    }
    newQueue->i = newQueue->j = 0;
    newQueue->array = NULL;
    return newQueue;
};

// 队为空返回true,不为空时返回false
bool is_empty_queue(Queue *tree)
{
    return (tree->i == tree->j);
};

// 结点指针出队
void *del_queue(Queue *tree)
{
    if (is_empty_queue(tree))
        return NULL;

    void *queueNode = tree->array[tree->i];
    tree->i++;
    return queueNode;
};

// 结点指针入队
void add_queue(Queue *tree, void *node)
{
    if (tree == NULL || node == NULL)
        return;

    if (tree->array == NULL)
    {
        tree->array = (void **)malloc(sizeof(void *));
        if (tree->array == NULL)
            return;
    }

    tree->array[tree->j] = node;
    tree->j++;
};

// 释放队列
void free_queue(Queue *tree)
{
    if (tree)
    {
        free(tree->array);
        free(tree);
    }
};

BiTNode *transform(CSNode *root)
{
    if (!root)
        return NULL;

    BiTree biTree = (BiTree)malloc(sizeof(BiTree));
    biTree->data = root->data;
    biTree->left = biTree->right = NULL;

    Queue *queue = create_queue();
    Queue *BiQueue = create_queue();
    add_queue(queue, root);
    add_queue(BiQueue, biTree);
    // bool a = is_empty_queue(queue);
    while (!is_empty_queue(queue))
    {
        CSNode *csNode = del_queue(queue);
        BiTree biNode = del_queue(BiQueue);

        BiTree biPtr = NULL;

        for (int i = 0; i < MAX_CHILDREN_NUM; i++)
        {
            if (csNode->children[i])
            {
                BiTree newBiNode = (BiTree)malloc(sizeof(BiTree));
                newBiNode->data = csNode->children[i]->data;
                newBiNode->left = newBiNode->right = NULL;

                if (i == 0)
                    (biNode)->left = newBiNode;
                else
                    (biPtr)->right = newBiNode;
                biPtr = newBiNode;

                add_queue(queue, csNode->children[i]);
                add_queue(BiQueue, newBiNode);
                PrintBiTree(biTree);
                printf("\n");
            }
        }
    }
    free_queue(queue);
    // free_queue(BiQueue);
    return biTree;
}

void PrintBiTree(BiTree root)
{
    if (!root)
        return;
    printf("%d ", (root)->data);
    PrintBiTree((root)->left);
    PrintBiTree((root)->right);
}

int main(int argc, char const *argv[])
{
    // Queue *testQueue = create_queue();
    CSNode *root = (CSNode *)malloc(sizeof(CSNode));
    (*root).data = 1;
    for (int i = 0; i < MAX_CHILDREN_NUM; i++)
    {
        (*root).children[i] = (CSNode *)malloc(sizeof(CSNode));
        for (int j = 0; j < MAX_CHILDREN_NUM; j++)
        {
            (*root).children[i]->children[j] = NULL;
        }

        (*root).children[i]->data = i + 2;
    }
    for (int i = 0; i < MAX_CHILDREN_NUM; i++)
    {
        (*root).children[0]->children[i] = (CSNode *)malloc(sizeof(CSNode));
        for (int j = 0; j < MAX_CHILDREN_NUM; j++)
        {
            (*root).children[0]->children[i]->children[j] = NULL;
        }
        (*root).children[0]->children[i]->data = i + 2 + 5;
    }
    BiTree BiTree = transform(root);
    PrintBiTree(BiTree);
    system("pause");
    return 0;
}
