#include <stdio.h>
#include <ctype.h>

/*

翻译（Translation）

编写程序可以把字母格式的电话号码翻译成数值格式：

Enter phone number: CALLATT

2255288

如果没有电话在身边,参考这里给出的字母在键盘上的对应关系：（2=ABC，3=DEF，4=GHI，5=JKL，6=MNO，7=PQRS，8=TUV，9=WXYZ）原始电话号码中的非字母字符（例如数字或标点符号）保持不变：

Enter phone number: 1-800-COL-LECT1-800-265-5328

可以假设任何用户输入的字母都是大写字母。

输出范例：

Enter phone number: 1-DCKS-A2D-OLED

1-3257-223-6533

*/

int main()
{
    char ch;
    while ((ch = getchar()) != '\n')
    {

        switch (ch)
        {
        case 'A':
        case 'B':
        case 'C':
            putchar('2');
            break;
        case 'D':
        case 'E':
        case 'F':
            putchar('3');
            break;
        case 'G':
        case 'H':
        case 'I':
            putchar('4');
            break;
        case 'J':
        case 'K':
        case 'L':
            putchar('5');
            break;
        case 'M':
        case 'N':
        case 'O':
            putchar('6');
            break;
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
            putchar('7');
            break;
        case 'T':
        case 'V':
        case 'U':
            putchar('8');
            break;
        case 'Y':
        case 'W':
        case 'X':
        case 'Z':
            putchar('9');
            break;
        default:
            putchar(ch);
            break;
        }
    }

    return 0;
}
