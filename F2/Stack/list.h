#include <stdbool.h>
#define Stack_Size 50
typedef struct
{
    int elem[Stack_Size];
    int top;
} Stack;

bool push(Stack *S, int x);
bool pop(Stack *S, int *x);
void init_stack(Stack *S);

void init_stack(Stack *S)
{
    S->top = -1;
}

typedef struct _QueueNode
{
    int data;                // 数据域
    struct _QueueNode *next; // 指针域
} LinkQueueNode, *LinkQueue;