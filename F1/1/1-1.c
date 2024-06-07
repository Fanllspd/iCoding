#include <stdio.h>

/*

计算税金(Tax)

编写一个程序，要求用户输入一个美元数量，然后显示出增加 5% 税率后的相应金额。

Enter an amount: 100.00
with tax added: $105.00

输入的金额为大于 0 的两位数浮点数。

*/

int main()
{
    float a;
    printf("Enter an amount: ");
    scanf("%f", &a);
    a *= 1.05;
    printf("with tax added: $%.2f", a);
}