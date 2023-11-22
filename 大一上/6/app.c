#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab52.h" // 请不要删除本行头文件，否则检查不通过

extern int CurrentCnt;
CurrentCnt = 0;

/*

链表：01-软件界面控制

实现一个数字选项式的启动界面，程序输入数据为（1-8），参考界面如下：

  1.显示所有商品的信息
  2.修改某个商品的信息
  3.插入某个商品的信息
  4.删除某个商品的信息
  5.查找某个商品的信息
  6.商品存盘并退出系统
  7.对商品价格进行排序
  8.(慎用)删除所有内容
  其他.不存盘并退出系统

程序当输入1-8时，执行相关功能，完成后再次显示菜单让用户选择。当输入其它数值时，程序不存盘并退出系统。

本小题只需实现 main 函数即可，相关结构及函数声明如下：

#define GOODS_FILE_NAME "goodsinfo.txt"

#define MAX_ID_LEN 30

#define MAX_NAME_LEN 30

#define MAX_PRICE_LEN 30

#define MAX_DISCOUNT_LEN 30
typedef struct {
char goods_id[MAX_ID_LEN];
char goods_name[MAX_NAME_LEN];
int goods_price;
char goods_discount[MAX_DISCOUNT_LEN];
int goods_amount;
int goods_remain;
} GoodsInfo;


typedef struct node
{
GoodsInfo data;
struct node *next;
} GoodsList;


GoodsInfo read_goods_info();
void init_list(GoodsList **pL);
void destory_list(GoodsList **pL);
void destory_list_and_file(GoodsList **pL);
int save_to_file(GoodsList *L);
void output_one_item(GoodsList *L);
void output_all_items(GoodsList *L);
bool insert_item(GoodsList *L, GoodsInfo item, int choice);
bool delete_item(GoodsList *L, char* goods_id);
GoodsList* search_item(GoodsList *L, char* goods_id);
bool change_item(GoodsList *L, char* goods_id, GoodsInfo new_info);
void bubble_sort(GoodsList *L);
int read_line(char str[], int n);

该部分声明已包含在 “lab52.h”中。

*/

int main()
{
    int code;
    GoodsList *GoodsList;
    init_list(&GoodsList);
    char id[MAX_ID_LEN];

    char *list = "1.显示所有商品的信息\n2.修改某个商品的信息\n3.插入某个商品的信息\n4.删除某个商品的信息\n5.查找某个商品的信息\n6.商品存盘并退出系统\n7.对商品价格进行排序\n8.(慎用)删除所有内容\n其他.不存盘并退出系统";
    while (1)
    {
        printf("%s", list);
        scanf("%d", &code);
        switch (code)
        {

        case 1:
            output_all_items(GoodsList);
            break;

        case 2:
        {
            read_line(id, MAX_ID_LEN);
            GoodsInfo newInfo = read_goods_info();
            change_item(GoodsList, id, newInfo);
            break;
        }
        case 3:
        {
            int choice;
            scanf("%d", &choice);
            GoodsInfo newInfo = read_goods_info();
            insert_item(GoodsList, newInfo, choice);
            break;
        }
        case 4:
        {
            read_line(id, MAX_ID_LEN);
            delete_item(GoodsList, id);
            break;
        }
        case 5:
        {
            read_line(id, MAX_ID_LEN);
            search_item(GoodsList, id);
            break;
        }
        case 6:
            save_to_file(GoodsList);
            destory_list(&GoodsList);
            return 0;
            // break;
        case 7:
            bubble_sort(GoodsList);
            break;
        case 8:
            destory_list_and_file(&GoodsList);
            break;

        default:
            destory_list(&GoodsList);
            return 0;
        }
    }
}

/*

链表：02-初始化

函数原型：void init_list(GoodsList **L)

其中 *L 为指向链表头结点的指针，L为指向链表头结点指针的地址，init_list首先创建链表的头结点，之后读取goodsinfo.txt(示例文件下载)中的商品信息，并初始化链表，函数执行后，需确保 *L 为指向链表头结点的指针。

init_list 实现商品信息链表的初始化，函数从已有的商品信息文件goodsinfo.txt(示例文件下载)中读入商品信息，并且分配内存保存至链表中。
为了方便在表头插入和删除结点的操作，经常在表头结点（存储第一个元素的结点）的前面增加一个结点，称之为头结点或表头附加结点。这样原来的表头指针由指向第一个元素的结点改为指向头结点，头结点的数据域为空，头结点的指针域指向第一个元素的结点。

注：使用 fopen 函数打开文件时，文件名必须为 GOODS_FILE_NAME，否则检测不通过。

*/

void init_list(GoodsList **pL)
{
    *pL = (GoodsList *)malloc(sizeof(GoodsList));
    (*pL)->next = NULL;
    GoodsList *Cur = *pL;
    GoodsInfo info;

    FILE *f;
    f = fopen(GOODS_FILE_NAME, "r");
    if (!f)
    {
        perror("open file for reading");
        exit(0);
    }
    while (fscanf(f, "%s\t%s\t%d\t%s\t%d\t%d\n",
                  info.goods_id,
                  info.goods_name,
                  &info.goods_price,
                  info.goods_discount,
                  &info.goods_amount,
                  &info.goods_remain) != EOF)
    {
        GoodsList *L = (GoodsList *)malloc(sizeof(GoodsList));
        L->data = info;
        L->next = Cur->next;
        Cur->next = L;
        Cur = Cur->next;
        CurrentCnt++;
    }
    fclose(f);
    f = NULL;
}

/*

链表：03-插入

函数原型：bool insert_item(GoodsList *L, GoodsInfo goodsInfo, int choice)，

L为指向链表头结点的指针，函数根据choise的值，将goodsInfo插入到链表的指定位置，如果成功插入，函数返回true，如果未插入，函数返回false。

分别实现头插法、尾插法，中间位置插入三种:
用户输入0，将商品信息插入到链表尾部；
用户输入1，将商品信息插入到链表头部；
用户输入其它正整数i，将商品信息插入到链表中间第i号位置, 例如：输入3，应该在第二个节点后插入新节点

*/

bool insert_item(GoodsList *L, GoodsInfo item, int choice)
{
    GoodsList *pL = (GoodsList *)malloc(sizeof(GoodsList));
    pL->data = item;

    GoodsList *Cur = L;

    switch (choice)
    {
    case 0:
    {
        while (Cur->next)
            Cur = Cur->next;
        pL->next = NULL;
        Cur->next = pL;
        break;
    }
    case 1:
        pL->next = L->next;
        L->next = pL;
        break;
    default:
    {
        int k = 1;
        while (k++ != choice)
        {
            if (!Cur->next || choice < 0)
                return false;

            Cur = Cur->next;
        }

        pL->next = Cur->next;
        Cur->next = pL;
        break;
    }
    }
    CurrentCnt++;
    return true;
}

/*

链表：04-删除节点

函数原型：bool delete_item(GoodsList *L, char* goods_id)

其中L为指向链表头结点的指针，goods_id为要删除商品的ID；

如果成功删除，函数返回true，否则返回false。

delete_item 根据商品的ID来删除对应的商品信息，商品查找通过字符串比较的方式，查找到后释放对应指针指向的内存区域，完成删除。

*/

bool delete_item(GoodsList *L, char *goods_id)
{
    GoodsList *Cur = L, *Del = Cur->next;
    while (Del)
    {
        if (!strcmp(Del->data.goods_id, goods_id))
        {
            Cur->next = Del->next;
            free(Del);
            CurrentCnt--;
            return true;
        }
        Del = Del->next;
        Cur = Cur->next;
    }
    return false;
}

/*

链表：05-查找

函数原型：GoodsList* search_item(GoodsList *L, char* goods_id)

其中L为指向链表头结点的指针，goods_id为要查找商品的ID；

如果找到该商品，函数返回该商品对应的结点指针，否则返回 NULL.

根据输入的商品 ID 来查找对应的商品信息，商品 ID 的判断用字符串比较的方式来实现，然后调用格式化显示查找到的商品信息.

*/

GoodsList *search_item(GoodsList *L, char *goods_id)
{
    GoodsList *Cur = L;
    while (Cur)
    {
        if (!strcmp(Cur->data.goods_id, goods_id))
        {
            return Cur;
        }
        Cur = Cur->next;
    }
    return NULL;
}

/*

链表：06-修改

函数原型：bool change_item(GoodsList *L, char* goods_id, GoodsInfo new_info)

其中 L 为指向链表头结点的指针，goods_id 为要修改的商品 ID，new_info 为该商品的最新数据。函数成功修改后返回true，否则返回 false。

*/

bool change_item(GoodsList *L, char *goods_id, GoodsInfo new_info)
{
    GoodsList *Cur = L;
    while (Cur)
    {
        if (!strcmp(Cur->data.goods_id, goods_id))
        {
            Cur->data = new_info;
            return true;
        }
        Cur = Cur->next;
    }
    return false;
}

/*

链表：07-显示单个节点

函数原型：void output_one_item(GoodsList *p)，函数显示结点为 p 的商品信息。

*/

void output_one_item(GoodsList *L)
{
    /*
    printf("%s", L->data.goods_id);
    printf("%s", L->data.goods_name);
    printf("%d", L->data.goods_price);
    printf("%s", L->data.goods_discount);
    printf("%d", L->data.goods_amount);
    printf("%d", L->data.goods_remain);
    */
    printf("goods_id:%s\t", L->data.goods_id);
    printf("goods_name:%s\t", L->data.goods_name);
    printf("goods_price:%d\t", L->data.goods_price);
    printf("goods_discount:%s\t", L->data.goods_discount);
    printf("goods_amount:%d\t", L->data.goods_amount);
    printf("goods_remain:%d\n", L->data.goods_remain);
}

/*

链表：08-显示所有节点

函数原型：void output_all_items(GoodsList *L)，

L为指针链表头结点的指针，output_all_items 调用 output_one_item 函数，将链表中所有的商品信息以格式化的方式打印输出到屏幕上。

*/

void output_all_items(GoodsList *L)
{
    GoodsList *Cur = L->next;
    while (Cur)
    {
        output_one_item(Cur);
        Cur = Cur->next;
    }
}

/*

链表：09-释放链表

函数原型：void destory_list(GoodsList **L)，

该函数释放包括头结点在内的所有结点，完成后指向链表头结点的指针为NULL。

*/

void destory_list(GoodsList **pL)
{
    GoodsList *Cur = *pL, *Des;
    while (Cur->next)
    {
        Des = Cur->next;
        Cur->next = Des->next;
        free(Des);
    }
    free(*pL);
    (*pL) = NULL;
}

/*

链表：10-释放链表并删除文件

函数原型：void destory_list_and_file(GoodsList **L)，

该函数调用destory_list释放包括头结点在内的所有结点，将指向链表头结点的指针为NULL，最后删除存储商品信息的文件goodinfo.txt。

*/

void destory_list_and_file(GoodsList **pL)
{
    destory_list(pL);
    remove("goodsinfo.txt"); // iCoding貌似识别不了GOODS_FILE_NAME
}

/*

链表：11-保存文件

函数原型：int save_to_file(GoodsList *L)

将当前链表所有的商品信息保存到文件 goodsinfo.txt 中，其中L为指向链表头结点的指针，保存成功后，该函数返回商品的数量。

*/

int save_to_file(GoodsList *L)
{
    if (!L)
        return 0;
    GoodsList *Cur = L->next;
    FILE *f = fopen("goodsinfo.txt", "w"); // iCoding貌似识别不了GOODS_FILE_NAME
    int counts = 0;
    if (!f)
        return 0;
    while (Cur)
    {

        fprintf(f, "%s\t%s\t%d\t%s\t%d\t%d\n",
                Cur->data.goods_id,
                Cur->data.goods_name,
                Cur->data.goods_price,
                Cur->data.goods_discount,
                Cur->data.goods_amount,
                Cur->data.goods_remain);

        Cur = Cur->next;
        counts++;
    }

    fclose(f);
    f = NULL;
    return counts;
}

/*

链表：12-排序

函数原型：void bubble_sort(GoodsList *L)

L为指向链表头结点的指针，该函数利用冒泡排序算法，按价格从低到高对商品进行排序。

*/

void bubble_sort(GoodsList *L)
{
    GoodsList *Cur = L->next;
    GoodsInfo temp;
    for (int i = 0; i < CurrentCnt - 1; i++)
    {
        for (int j = 1; j < CurrentCnt - i; j++)
        {
            if (Cur->data.goods_price > Cur->next->data.goods_price)
            {
                temp = Cur->data;
                Cur->data = Cur->next->data;
                Cur->next->data = temp;
                // output_all_items(L);
                // printf("\n");
            }
            Cur = Cur->next;
        }
        Cur = L->next;
    }
}

/*

链表：13-读商品信息

函数原型：GoodsInfo read_goods_info()

该函数调用read_line及scanf等函数，按“商品ID、商品名称、商品价格、商品折扣、商品数量、商品剩余数量”的顺序让用户输入，并将这些信息保存到 GoodsInfo 结构体中，函数最后返回该结构体。

*/

GoodsInfo read_goods_info()
{
    GoodsInfo goods;
    read_line(goods.goods_id, MAX_ID_LEN);
    read_line(goods.goods_name, MAX_NAME_LEN);
    scanf("%d", &goods.goods_price);
    read_line(goods.goods_discount, MAX_DISCOUNT_LEN);
    scanf("%d", &goods.goods_amount);
    scanf("%d", &goods.goods_remain);
    return goods;
}