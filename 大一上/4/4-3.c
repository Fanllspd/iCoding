#include <stdio.h>
#include <string.h>

/*

最大最小单词简略版（The Biggest and Smallest Words）

编写程序找出一组单词中“最小”单词和“最大”单词。

用户输入单词后，程序根据字典顺序决定排在最前面和最后面的单词。

当用户输入4个字母的单词时，程序停止读入。假设所有单词都不超过20个字母。

输出范例1：
Enter word: dog
Enter word: zebra
Enter word: rabbit
Enter word: catfish
Enter word: walrus
Enter word: cat
Enter word: fish


Smallest word: cat
Largest word zebra


输出范例2：


Enter word: computer
Enter word: ink
Enter word: light
Enter word: bookrack
Enter word: book


Smallest word: book
Largest word: light

*/

int isMin(char chNew[], char chOld[])
{
    for (int i = 0; i < strlen(chNew); i++)
    {

        if (chNew[i] < chOld[i])
            return 1;
        if (chNew[i] != chOld[i])
            return 0;
    }
    return 0;
}
int isMax(char chNew[], char chOld[])
{
    for (int i = 0; i < strlen(chNew); i++)
    {
        if (chNew[i] > chOld[i])
            return 1;
        if (chNew[i] != chOld[i])
            return 0;
    }
    return 1;
}
char *getSmallest(char words[][30], int counts)
{
    int record = 0;
    for (int i = 1; i < counts; i++)
    {
        if (isMin(words[i], words[record]))
        {
            record = i;
        }
    }
    // printf(words[record]);
    return words[record];
}
char *getBiggest(char words[][30], int counts)
{
    int record = 0;
    for (int i = 1; i < counts; i++)
    {

        if (isMax(words[i], words[record]))
        {
            record = i;
        }
    }
    // printf(words[record]);
    return words[record];
}

int main()
{
    char words[30][30];
    int len = 0, counts = 0;
    while (len != 4)
    {
        scanf("%s", words[counts++]);
        len = strlen(words[counts - 1]);

        // words[counts++] = ch;
        //  foundSmallest(len);
    }
    printf("Smallest word: %s\n", getSmallest(words, counts));
    printf("Largest word: %s", getBiggest(words, counts));

    return 0;
}
