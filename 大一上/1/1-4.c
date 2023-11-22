#include <stdio.h>

/*

日期格式转化（Date Format Convention）

编写一个程序，以月/日/年（即 mm/dd/yy）的格式接受用户录入的日期信息，并以年月日（即yyyymmdd）的格式将其显示出来。

Enter a date (mm/dd/yyyy): 2/17/2011
You entered the date 20110217

*/

int main()
{
    int m, d, y;
    printf("Enter a date (mm/dd/yyyy): ");
    scanf("%d/%d/%d", &m, &d, &y);
    printf("You entered the date %04d%02d%02d", y, m, d);
    return 0;
}
