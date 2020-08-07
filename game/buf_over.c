#include <stdio.h>
#include <string.h>
/*
gcc:
  gcc -fno-stack-protector buf_over.c 
  如果不加这个flag,运行时会报：　*** stack smashing detected ***: <unknown> terminated
dis: 
  (gdb) disassemble main

attack:
  $ ./a.out
  pass2
  $ ./a.out
  pass1234
  you win!
  这说明：matached的位置不是贴着buf的
*/

int main()
{
  char matched = '\0';
  char buf[5];
  //printf("input pass\n");
  gets(buf);
#define GOODPASS "PASS"

  if (strcmp(buf, GOODPASS) == 0)
  {
    matched = 1;
  }
  if (matched)
  {
    printf("you win!\n");
  }
  return 0;
}