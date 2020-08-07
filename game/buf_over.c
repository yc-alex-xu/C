#include <stdio.h>
#include <string.h>
/*
gcc:
  gcc -fno-stack-protector buf_over.c 

dis: 
  (gdb) disassemble main

attack:

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