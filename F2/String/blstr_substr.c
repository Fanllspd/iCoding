#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dsstring.h" // 请不要删除，否则检查不通过

/**
 * @description:
 * @param {BLString} *str
 * @return {*}
 */
void print_blstr(BLString *str)
{
    int length = 0;
    Block *current = str->head;
    while (current != NULL)
    {
        for (int i = 0; i < BLOCK_SIZE; i++)
        {
            printf("%c", current->ch[i]);
            length++;
        }
        current = current->next;
    }
    printf("    len: %d", length);
    printf("\n");
}

/**
 * @description:
 * @param {BLString} *bls
 * @param {char} str
 * @return {*}
 */
void generate_blstr(BLString *bls, char str[])
{
    BLString *pB = bls;
    Block *newBlock = NULL, *tail = NULL;

    int len = strlen(str);
    int counts = len / BLOCK_SIZE;
    if (len % BLOCK_SIZE)
        counts += 1;

    for (int i = 0; i < counts; i++)
    {
        newBlock = (Block *)malloc(sizeof(Block));
        if (pB->head)
        {
            tail->next = newBlock;
            tail = tail->next;
        }
        else
            bls->head = tail = newBlock;

        int copy_len = (len >= BLOCK_SIZE) ? BLOCK_SIZE : len;
        memcpy(tail->ch, str + BLOCK_SIZE * i, copy_len);

        len -= copy_len;

        if (len <= 0)
            memset(tail->ch + copy_len, BLS_BLANK, BLOCK_SIZE - copy_len);

        bls->tail = tail;
        tail->next = NULL;
        bls->len += copy_len;
    }
}

/**
 *
 * src为要查找的字符串
 * pos为子串开始的下标
 * len为子串的长度
 * sub在函数调用运行前指向一个已经初始化好的空串，
    在函数返回时，sub指向串src从第pos个字符起长度为len的子串
    函数查找成功返回true，参数不正确返回 false
*/
/**
 * @description:
 * @param {BLString} src
 * @param {int} pos
 * @param {int} len
 * @param {BLString} *sub
 * @return {*}
 */
bool blstr_substr(BLString src, int pos, int len, BLString *sub)
{
    // if (pos < 0 || len < 0 || pos + len > src.len)
    //     return false;

    if (len <= 0)
        return false;

    int index = pos / BLOCK_SIZE, offset = pos % BLOCK_SIZE;
    Block *pBh = src.head;

    int now = 0;
    while (now++ < index)
        pBh = pBh->next;

    int counts = 0, counts2 = offset;

    Block *newBlock = NULL;
    while (pBh && counts < len)
    {
        if (counts + pos >= src.len)
            break;
        if (counts % BLOCK_SIZE == 0)
        {
            // pBh = pBh->next;
            newBlock = (Block *)malloc(sizeof(Block));
            if (newBlock == NULL)
                return false;

            if (sub->head)
            {
                sub->tail->next = newBlock;
                sub->tail = sub->tail->next;
            }
            else
            {
                sub->head = sub->tail = newBlock;
            }
            sub->tail->next = NULL;
        }
        newBlock->ch[counts++ % BLOCK_SIZE] = pBh->ch[counts2++ % BLOCK_SIZE];

        if (counts2 % BLOCK_SIZE == 0)
        {
            pBh = pBh->next;
            counts2 = 0;
        }
    }
    while (counts % BLOCK_SIZE != 0)
    {
        newBlock->ch[counts % BLOCK_SIZE] = BLS_BLANK;
        counts++;
    }
    sub->tail->next = NULL;
    if (pos + len > src.len)
        sub->len = src.len - pos;
    else
        sub->len = len;

    // free(newBlock);
    return true;
}

int main(int argc, char const *argv[])
{

    BLString bls;
    // = (BLString *)malloc(sizeof(BLString));
    blstr_init(&bls);

    char str[100] = "abcdefghijklmnopqrstuvwxyABC";
    generate_blstr(&bls, str);
    printf("Source string: ");
    print_blstr(&bls);

    // 定义并初始化子串
    BLString sub;
    blstr_init(&sub);

    // 查找子串
    int pos = 10;
    int len = 31;

    if (blstr_substr(bls, pos, len, &sub))
    {
        printf("Substring from position %d with length %d: ", pos, len);
        print_blstr(&sub);
        printf("\n%d", sub.len);
        printf("\n%c", sub.tail->ch[3]);
    }
    else
    {
        printf("Substring not found.\n");
        print_blstr(&sub);
    }
    // printf("%d", blstr_substr(src, 0, 4, sub));
    return 0;
}
