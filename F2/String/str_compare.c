#include <stdio.h>
#include <stdlib.h>
#include "dsstring.h" //请不要删除，否则检查不通过

int str_len(const char *str)
{
    int length = 0;
    while (str[length] != '\0')
        length++;
    return length;
}

int str_compare(const char *ptr1, const char *ptr2)
{
    int lenOfPtr1 = str_len(ptr1);
    int lenOfPtr2 = str_len(ptr2);
    int max = lenOfPtr1 >= lenOfPtr2 ? lenOfPtr1 : lenOfPtr2;

    for (int i = 0; i < max; i++)
    {
        if (ptr1[i] == ptr2[i])
            continue;
        if (ptr1[i] < ptr2[i])
        {
            if (ptr1[i] >= 'A' && ptr1[i] <= 'Z' && (ptr2[i] - ptr1[i] == 32))
                continue;
            return ptr1[i] - ptr2[i];
        }
        if (ptr1[i] > ptr2[i])
        {
            if (ptr1[i] >= 'a' && ptr1[i] <= 'z' && (ptr1[i] - ptr2[i] == 32))
                continue;
            return ptr1[i] - ptr2[i];
        }
    }

    return 0;
}

int main(int argc, char const *argv[])
{
    int result = str_compare("1krFrTM8u41XnaCeAjM1W07T377t0x", "1krFrTM8u41XnaCeAjM1W07T377T0X");
    printf("%d", result);
    return 0;
}
