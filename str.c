/* 
to verify whether sprintf will  termiated the buf with \0
the answer is :yes
*/
#include <stdio.h>
int main()
{
    char name[8];
    sprintf(name, "%c%c%c", 'a', 'b', 'c');
    return 0;
}
