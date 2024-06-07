#include <stdio.h>

/*

计算账单（Bills）

编写⼀个程序，要求用户输出⼀个美元数量，然后显示出如何用最少20美元、10美元、5美元和1美元来付款。

Enter a dollar amount: 93
$20 bills: 4
$10 bills: 1
$5 bills: 0
$1 bills: 3

*/

int main()
{
    int dollar, b, c, d, e;
    printf("Enter a dollar amount: ");
    scanf("%d", &dollar);
    b = dollar / 20;
    c = (dollar - b * 20) / 10;
    d = (dollar - b * 20 - c * 10) / 5;
    e = dollar - b * 20 - c * 10 - d * 5;
    printf("$20 bills: %d\n", b);
    printf("$10 bills: %d\n", c);
    printf("$5 bills: %d\n", d);
    printf("$1 bills: %d\n", e);
}