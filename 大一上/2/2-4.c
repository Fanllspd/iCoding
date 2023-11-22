#include <stdio.h>

/*

将百分制转换为等级制（Centesimal-grade to Letter-grade）

利用switch语句编写一个程序，把用数字表示的成绩转化为字母表示的等级。

使用下面的等级评定规则：A为90~100，B为80~89，C为70~79，D为60~69，F为0~59。如果成绩大于100或小于0显示出错信息。

输出范例：
Enter numerical grade: 84
Letter grade: B

Enter numerical grade: -1
Error, grade must be between 0 and 100.

提示：把成绩拆分成 2 个数字，然后使用 switch 语句判定十位上的数字。

*/

int main()
{
    int grade;
    printf("Enter numerical grade: ");
    scanf("%d", &grade);
    if (grade < 0 || grade > 100)
    {
        printf("Error, grade must be between 0 and 100.\n");
        return 0;
    }
    grade /= 10;
    switch (grade)
    {
    case 10:
        printf("Letter grade: A");
        break;
    case 9:
        printf("Letter grade: A");
        break;
    case 8:
        printf("Letter grade: B");
        break;
    case 7:
        printf("Letter grade: C");
        break;
    case 6:
        printf("Letter grade: D");
        break;
    case 5:
        printf("Letter grade: F");
        break;
    case 4:
        printf("Letter grade: F");
        break;
    case 3:
        printf("Letter grade: F");
        break;
    case 2:
        printf("Letter grade: F");
        break;
    case 1:
        printf("Letter grade: F");
        break;
    case 0:
        printf("Letter grade: F");
        break;

    default:
        printf("Error, grade must be between 0 and 100.\n");
        break;
    }
    return 0;
}
