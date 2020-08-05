#include <stdio.h>
#include "toolkit.h"

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
  printf("before swap %d %d\n", a, b);
  swap_int(&a, &b);
  printf("after  swap %d %d\n", a, b);
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

int avg_int(int a, int b)
{
  return (a >> 1) + (b >> 1) + (a & b & 1);
}

void avg_test(void)
{
  FUNC_HEAD();
  unsigned int t = avg(-1, -5);
  printf("avg return: %ud %d %d\n",t,(int)t,avg_int(3,-3));
}

int main()
{
  sign_test();
  swap_test();
  endian_test();
  avg_test();
  return 0;
}
