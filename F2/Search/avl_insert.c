#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

#define max(a, b) ((a) > (b) ? (a) : (b))

int get_height(node_t *root)
{
    if (root == NULL)
        return 0;
    return 1 + max(get_height(root->left), get_height(root->right));
}

int get_balance_factor(node_t *root)
{
    return get_height(root->left) - get_height(root->right);
}

/*

          2:Y
           / \
        1:X   YL
         / \
   1/-1:XL  XR
       /  \
NEW:  A    B
        or

--RightRotation
==>

          0: X
           /   \
        0:XL    Y
         / \   / \
        A   B XR  YL
          or
*/
node_t *right_rotate(node_t *y)
{
    node_t *x = y->left;
    y->left = x->right;
    x->right = y;

    y->parent = x;
    if (y->left != NULL)
        y->left->parent = y;

    y->height = get_height(y);
    x->height = get_height(x);
    return x;
}

/*

            Y:2
           / \
          YL  X:1
             / \
            XL  XR:1/-1
               / \
        NEW:  A   B
                or

--LeftRotation
==>

             X:0
           /   \
          Y     XR:1/-1
         / \   /  \
        YL  XL A   B
                 or

*/
node_t *left_rotate(node_t *y)
{
    node_t *x = y->right;
    y->right = x->left;
    x->left = y;

    y->parent = x;
    if (y->right != NULL)
        y->right->parent = y;

    y->height = get_height(y);
    x->height = get_height(x);
    return x;
}

node_t *avl_insert(node_t *root, int val)
{
    if (root == NULL)
    {
        node_t *newNode = (node_t *)malloc(sizeof(node_t));
        newNode->val = val;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->parent = NULL;
        newNode->height = 1;

        return newNode;
    }

    if (val < root->val)
    {
        root->left = avl_insert(root->left, val);
        root->left->parent = root;
    }
    else if (val > root->val)
    {

        root->right = avl_insert(root->right, val);
        root->right->parent = root;
    }
    else
    {
        return root;
    }

    root->height = get_height(root);

    int bf = get_balance_factor(root);

    // LL
    if (bf > 1 && val < root->left->val)
        return right_rotate(root);

    // LR
    if (bf > 1 && val > root->left->val)
    {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    // RR
    if (bf < -1 && val > root->right->val)
        return left_rotate(root);

    // RL
    if (bf < -1 && val < root->right->val)
    {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
    return root;
}

// 打印给定层次的节点
void print_current_level(node_t *root, int level)
{
    if (root == NULL)
    {
        printf("   ");
        return;
    }
    if (level == 1)
    {
        printf("%3d", root->val);
    }
    else if (level > 1)
    {
        print_current_level(root->left, level);
        print_current_level(root->right, level);
    }
}

// 层次遍历打印树
void print_tree(node_t *root)
{
    int height = get_height(root);
    for (int i = 1; i <= height; i++)
    {
        print_current_level(root, i);
        printf("\n");
    }
}

int main(int argc, char const *argv[])
{
    node_t *root = NULL;
    root = avl_insert(root, 22);
    root = avl_insert(root, 16);
    root = avl_insert(root, 23);
    root = avl_insert(root, 20);
    root = avl_insert(root, 30);
    printf("%d", get_height(root));
    printf("Tree structure:\n");
    print_tree(root);
    return 0;
}
