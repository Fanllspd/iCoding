#include <stdio.h>
#include <math.h>

/*

偶数平方（Square of Even Number）

编写程序，提示用户输入一个数 n，然后显示出 1~n 的所有偶数的平方值。

输出范例：
Enter a number: 100
4
16
36
64
100

Enter a number: 50
4
16
36

*/

int main()
{
    int n, i = 0;
    printf("Enter a number: ");
    scanf("%d", &n);
    while (i * i < n)
    {
        i += 2;
        printf("%d\n", i * i);
    }
    return 0;
}
