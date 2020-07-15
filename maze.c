/*
some puzzling side of c language
tested via: gcc -std=c11 
*/
#include <stdio.h>
#include <unistd.h>
#include "toolkit.h"

/*
    difference between stdout & stderr
    stdout need "\n" or flush() explicitly.
    and return will flush the buffer implicitly
*/
inline void test_stdout_stderr();
void stdio_test()
{
    FUNC_HEAD();
    for (int i = 0; i < 3; i++)
    {
        fprintf(stdout, "-out-");
        fprintf(stderr, "-err-");
    }
}

void printf_test()
{
    FUNC_HEAD();
    int i = 43;
    printf("%d\n", printf("%d", printf("%d", i))); //4321
}

/*
二进制由 0 和 1 两个数字组成，使用时必须以0b或0B（不区分大小写）开头，
八进制由 0~7 八个数字组成，使用时必须以0开头（注意是数字 0，不是字母 o
十六进制由数字 0~9、字母 A~F 或 a~f（不区分大小写）组成，使用时必须以0x或0X（不区分大小写）开头
*/
void octal_test()
{
    FUNC_HEAD();
#define SIZEOF(arr) (sizeof(arr) / sizeof(arr[0]))
#define PrintInt(expr) printf("%s:%o\n", #expr, (expr))
    /* The powers of 10 */
    int pot[] = {
        01,
        010,
        0100,
        100}; //以0 打头的都被看成8进制

    for (int i = 0; i < SIZEOF(pot); i++)
        PrintInt(pot[i]);
}

/*
“hello”[2] == 2[“hello”]
*/
void substr_test()
{
    FUNC_HEAD();
    int a = 3, b = 5;
    printf(&a["Ya!Hello! how is this? %s\n"], &b["junk/super"]);
    printf(&a["WHAT%c%c%c  %c%c  %c !\n"], 1 ["this"],
           2 ["beauty"], 0 ["tool"], 0 ["is"], 3 ["sensitive"], 4 ["CCCCCC"]);
}

int main()
{
    stdio_test();
    printf_test();
    octal_test();
    substr_test();
    return 0;
}