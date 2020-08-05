#include <stdio.h>
#include <assert.h>
#include "toolkit.h"
/* 
to verify whether sprintf will  termiated the buf with \0
the answer is :yes
*/
void sprintf_test()
{
    FUNC_HEAD();
    char str[8];
    sprintf(str, "%c%c%c", 'a', 'b', 'c');
    printf("%s\n", str);
}

//handle the overlap issue just like libc
/* 
assert macro:
If the macro NDEBUG is defined (above the statement that includes assert.h!), the assert macro does absolutely nothing.
$gcc -DDEBUG -E test.c  -o a.c     用来传递DEBUG的定义
$clang -DDEBUG -E test.c  -o a.c
 */

/* 
bad example that  make garbage collection difficult or impossible
char *s = (char *) malloc(1024);
s -= 10000;
restrict是c99标准引入的，它只可以用于限定和约束指针，并表明指针是访问一个数据对象的唯一
且初始的方式.即它告诉编译器，所有修改该指针所指向内存中内容的操作都必须通过该指针来修改
关键字restrict有两个读者。一个是编译器，它告诉编译器可以自由地做一些有关优化的假定。
另一个读者是用户，他告诉用户仅使用满足restrict要求的参数。一般，编译器无法检查您
是否遵循了这一限制，如果您蔑视它也就是在让自己冒险。
*/

/*
char *strcpy(char *dest, const char *src);
*/
char *strcpy2(char *restrict strDest, const char *restrict strSrc)
{
    assert(strDest != NULL && strSrc != NULL && strSrc != strDest);
    char *address = strDest;
    if (strDest < strSrc)
    {
        for (; *strSrc;)
        {
            *strDest = *strSrc;
            strDest++;
            strSrc++;
        }
        *strDest = '\0';
    }
    else
    {
        for (; *strSrc;)
        {
            strDest++;
            strSrc++;
        }
        for (; address <= strDest;)
        {
            *strDest = *strSrc;
            strDest--;
            strSrc--;
        }
    }
    return address;
}

void strcpy_test()
{
    FUNC_HEAD();
    char str[30];
    char *p = &(str[5]);
    strcpy2(p, "123456");
    printf("the src=123456 the dest=%s\n", p);
}

int main()
{
    sprintf_test();
    strcpy_test();
    return 0;
}