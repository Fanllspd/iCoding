/*
 * @Author: Fanllspd Fanllspd@gmail.com
 * @Date: 2024-03-14 14:41:14
 * @LastEditors: Fanllspd Fanllspd@gmail.com
 * @LastEditTime: 2024-03-14 16:01:51
 * @FilePath: \F2\String\2.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dsstring.h"

/**
 * @description:
 * @param {char} *str
 * @return {*}
 */
int str_len(const char *str)
{
    int length = 0;
    while (str[length] != '\0')
        length++;
    return length;
}

/**
 * 参数说明:
 * in， 原始字符串，保持不变
 * out, 存放替换结果的字符串
 * outlen，out空间的大小
 * oldstr，要替换的旧字符串
 * newstr，替换成的新字符串
函数返回成功替换的次数，即有多少个子串被成功替换
在替换过程中，任何情况下所得字符串（及结束符）不应该超过 outlen，如果某次替换所得字符串的长度超过 outlen，则不进行这次替换操作，整个替换操作结束。如：
原始串为 "aaabbbccc"，outlen 为14, oldstr 为 "c"，newstr 为 "333" 时，两次替换后得 "aaabbb333333c"，此时字符串占用空间为14字节。
如果再进行替换，则会超出 out 所占用的空间，所以停止替换操作。此时函数应该返回 2, out指向的串为 "aaabbb333333c"
再如：原始串为 "aaabbbccc"，outlen 为10, oldstr 为 "b"，newstr 为 "123456"，进行替换后所得的串长度为14，与结束符一共占 15 个字节，超过outlen的10字节，此时不进行替换，函数应该返回 0。
*/
/**
 * @description:
 * @param {char} *in
 * @param {char} *out
 * @param {int} outlen
 * @param {char} *oldstr
 * @param {char} *newstr
 * @return {*}
 */
int str_replace(const char *in, char *out, int outlen,
                const char *oldstr, const char *newstr)
{
    int replaceCounts = 0,
        lenOfOldstr = str_len(oldstr),
        lenOfNewstr = str_len(newstr);

    int offset = 0, i = 0;

    for (int i = 0; i < outlen; i++)
    {
        out[i] = '\0';
    }
    while (in[i] != '\0')
    {
        int match = 1;
        for (int j = 0; j < lenOfOldstr; j++)
        {
            if (in[i + j] != oldstr[j])
            {
                match = 0;
                break;
            }
        }

        if (match && offset + str_len(in) - i - lenOfOldstr + lenOfNewstr < outlen)
        {
            for (int j = 0; j < lenOfNewstr; j++)
            {
                out[offset++] = newstr[j];
            }

            replaceCounts++;
            i += lenOfOldstr;
        }
        else
        {
            if (offset >= outlen - 1)
                return 0;
            out[offset] = in[i];
            offset++;
            i++;
        }

        // i++;
    }
    out[outlen] = '\0';
    return replaceCounts;
}
int main(int argc, char const *argv[])
{
    /* code */
    char result[100];
    // str_replace("aaabbbccc", result, 14, "c", "333");
    int a = str_replace("aaabbbccc", result, 14, "cc", "1234567");
    printf("%s,%d", result, a);
    return 0;
}
