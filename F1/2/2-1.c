#include <stdio.h>

/*

24小时制-12小时制转换(24-hour to 12-hour)

编写一个程序，要求用户输入 24 小时制的时间，将其转换为 12 小时制的格式。

Enter a 24-hour time: 21:11
Equivalent 12-hour time: 9:11 PM

Enter a 24-hour time: 0:01
Equivalent 12-hour time: 12:01 AM

注意，不要把12:00显示为0:00。

*/

int main(void)
{
    int a, b;
    printf("Enter a 24-hour time: ");
    scanf("%d:%d", &a, &b);
    if (a >= 13)
    {
        a -= 12;
        printf("Equivalent 12-hour time: %d:%02d PM", a, b);
        return 0;
    }
    if (a >= 12)
    {
        printf("Equivalent 12-hour time: %d:%02d PM", a, b);
    }
    if (a < 1)
    {
        a += 12;
        printf("Equivalent 12-hour time: %d:%02d AM", a, b);
        return 0;
    }
    printf("Equivalent 12-hour time: %d:%02d AM", a, b);
}
