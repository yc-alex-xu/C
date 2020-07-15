#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
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
  printf("&a=%p\n&b=%p\n&c=%p\n", &a, &b,&c);
}

//handle the overlap issue just like libc
/* 
assert macro:
If the macro NDEBUG is defined (above the statement that includes assert.h!), the assert macro does absolutely nothing.
$gcc -DDEBUG -E test.c  -o a.c     用来传递DEBUG的定义
$clang -DDEBUG -E test.c  -o a.c
 */
char *strcpy_alex(char *restrict strDest, const char *restrict strSrc)
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

void str_func_test()
{
  FUNC_HEAD();
  char str[30];
  char *p = &(str[5]);
  strcpy_alex(p, "123456");
  printf("the src=123456 the dest=%s\n", p);
}

int swap_int(int *p, int *q)
{
  *p ^= *q;
  *q ^= *p;
  *p ^= *q;
  return 0;
}

void swap_test()
{
  FUNC_HEAD();
  int a = 3, b = 4;
  printf("before swap %d %d\n",a,b);
  swap_int(&a, &b);
  printf("after  swap %d %d\n",a,b);
}

void endian_test()
{
  FUNC_HEAD();
  typedef union {
    int i;
    char c;
  } word_t;
  word_t w;
  w.i = 1;
  if (w.c == '\1')
    printf("little endian\n");
  else
    printf("big endian\n");
}

//~ 按位取反运算符
#define ISUNSIGNED(a) (a >= 0 && ~a >= 0)
#define ISUNSIGNED_T(type) ((type)0 - 1 > 0)
void sign_test(void)
{
  FUNC_HEAD();
  unsigned int ut = 1;
  printf("unsigned? %d\n", ISUNSIGNED(ut));
  printf("unsigned type ?%d\n", ISUNSIGNED_T(unsigned int));

  signed int st = 1;
  printf("unsigned? %d\n", ISUNSIGNED(st));
  printf("unsigned type? %d\n", ISUNSIGNED_T(signed int));
}

//如果不用这小技巧，求平均会overflow
unsigned int avg(unsigned int a, unsigned int b)
{
  return (a >> 1) + (b >> 1) + (a & b & 1);
}

void avg_test(void)
{
  FUNC_HEAD();
  printf("avg return: %ud\n", avg(-1, -1));
}

int main()
{
  char_space_test();
  sign_test();
  str_func_test();
  swap_test();
  endian_test();
  avg_test();
  return 0;
}
