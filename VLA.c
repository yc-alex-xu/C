#include <stdio.h>
#include <string.h>

void strdup2(const char * p)
{
    int len = strlen(p);	
    char s[len+1];
    strncpy(s,p,len+1);
    printf("after strcpy,s = %s\n",s);
}

int main()
{
    strdup2("OK");
    strdup2("still ok");
    strdup2("abcdefghijklmnopqrstuvwxyz");
}




