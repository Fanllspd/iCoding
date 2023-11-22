#include <stdio.h>

/*

逆序（Reversal）

编写程序读一条消息，然后逆序打印出这条消息。

输出范例：


Enter a message: Don't get mad, get even.
Reversal is: .neve teg ,dam teg t'noD


Enter a message: Hello, world!
Reversal is: !dlrow ,olleH


提示：一次读取消息中的一个字符（用getchar函数），并且把这些字符存储在数组中，当数组写满或者读到字符 '\n' 时停止读入。

*/

int main(void)
{
    char ch, arr[50];
    int i = 0;
    while ((ch = getchar()) != '\n')
    {
        arr[i] = ch;
        i++;
    }
    for (int j = i; j > -1; j--)
    {
        putchar(arr[j]);
    }

    return 0;
}
