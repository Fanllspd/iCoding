#include <stdio.h>

/*

出现次数（Number Occurrences）

修改如下程序，使其打印⼀份列表，显示出每个数字在数中出现的次数。

输出范例：

Enter a number: 41271092

Digit:	0	1	2	3	4	5	6	7	8	9
Occurrences:	1	2	2	0	1	0	0	1	0	1

*/

int main()
{
    int num;
    int occ[10] = {0};
    printf("Digit:	0	1	2	3	4	5	6	7	8	9");
    while ((num = getchar()) != '\n')
    {
        switch (num)
        {
        case '0':
            occ[0]++;
            break;
        case '1':
            occ[1]++;
            break;
        case '2':
            occ[2]++;
            break;
        case '3':
            occ[3]++;
            break;
        case '4':
            occ[4]++;
            break;
        case '5':
            occ[5]++;
            break;
        case '6':
            occ[6]++;
            break;
        case '7':
            occ[7]++;
            break;
        case '8':
            occ[8]++;
            break;
        case '9':
            occ[9]++;
            break;

        default:
            break;
        }
    }
    printf("Occurrences:");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", occ[i]);
    }

    return 0;
}
