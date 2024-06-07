#include <stdio.h>

/*

风速等级与描述（Wind Speed）

下面是用于测量风力等级的简化版，编写一个程序，要求用户输入风速（海里/小时），然后显示相应的描述。

速率（海里/⼩时）	描述
小于 1	Calm（无风）
1~3	Light air（轻风）
4~27	Breeze（微风）
28~47	Gale（⼤风）
48~63	Storm（暴风）
⼤于63	Hurricane（飓风）
输出范例：Enter a wind speed: 1

Light air

Enter a wind speed: 27

Breeze

*/

int main()
{
    int rate;
    printf("Enter a wind speed: ");
    scanf("%d", &rate);
    if (rate < 1)
    {
        printf("Calm");
    }
    else if (rate <= 3)
    {
        printf("Light air");
    }
    else if (rate <= 27)
    {
        printf("Breeze");
    }
    else if (rate <= 47)
    {
        printf("Gale");
    }
    else if (rate <= 63)
    {
        printf("Storm");
    }
    else
    {
        printf("Hurricane");
    }

    return 0;
}
