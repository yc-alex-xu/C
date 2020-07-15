#include <stdio.h>
#include "toolkit.h"

/* compiler 缺省优化，会考虑变量空间的paragrah, 所以即使代码中 char a,b 被 int c 隔开
   空间分配时还是会优化的
*/
void char_space_test()
{
    FUNC_HEAD();
    char a;
    int c;
    char b;
    printf("&a=%p\n&b=%p\n&c=%p\n", &a, &b, &c);
}

void char_sign_test()
{
    FUNC_HEAD();
    char c = -1;
    /*char 编译器可以实现为带符号的，也可以实现为不带符号的 */
    printf("char type is:%s\n", c < 0 ? "signed" : "unsigned");
    char *p;                  //char *:Null-character (‘\0’) terminated character arrays
    unsigned char *q = "abc"; /* in modern c it  work same as char */
    printf("%s\n", q);

    for (char i = 126; i < 127; ++i) //if <128, it will loop endless
    {
        printf("%d\n", i);
    }
}

int main()
{
    char_space_test();
    char_sign_test();
}