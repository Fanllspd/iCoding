#include <stdio.h>

/*

表达式求值（Expression Evaluation）

编写程序对表达式求值。

Enter an expression: 1+2.5*3
Value of expression: 10.5


表达式中的操作数是浮点数，运算符是+、-、*和/。表达式从左向右求值（所有运算符的优先级都⼀样）。


输出范例：


Enter an expression: 2+3*4-5/2
Value of expression: 7.5

*/

int main()
{
    char ch;
    float num, num2;
    scanf("%f", &num);
    while ((ch = getchar()) != '\n')
    {
        scanf("%f", &num2);
        switch (ch)
        {
        case '+':
            num += num2;
            break;

        case '-':
            num -= num2;
            break;
        case '*':
            num *= num2;
            break;
        case '/':
            num /= num2;
            break;
        default:
            break;
        }
    }
    printf("%f", num);
    return 0;
}
