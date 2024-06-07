#include <stdio.h>

/*

日历（Calendar Month）

编写程序显示单月的日历。用户指定这个月的天数和该月起始日是星期几。

输出范例：

Enter number of days in month: 31

Enter starting day of the week(1=Sun, 7=Sat): 3

日	一	二	三	四	五	六
 1	2	 3	 4	 5
 6	 7	 8	 9	10	11	12
13	14	15	16	17	18	19
20	21	22	23	24	25	26
27	28	29	30	31

*/

void outputCalender(int days, int start)
{
    start %= 8;
    int counts = 1;
    // printf("日\t一\t二\t三\t四\t五\t六\n");

    for (int i = 0; i < (days + start - 1) / 7 + 1; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if ((i == 0 && j < start - 1) || counts > days)
            {
                printf("\t");
                continue;
            }
            printf("%d\t", counts++);
        }
        printf("\n");
    }
}

int main()
{
    int days, start;
    scanf("%d", &days);
    scanf("%d", &start);
    outputCalender(days, start);

    return 0;
}
