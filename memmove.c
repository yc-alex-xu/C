#include <stdio.h>

/*
__np_anyptrlt(p1,p2)：A macro or function such that, for any two pointers p1 and p2，
__np_anyptrlt(p1,p2) evaluates to:
non-zero if p1 and p2 point within the same object and p1 is less than p2；
zero if p1 and p2 point within the same object and p1 is greater than p2；
an unspecified integer value if the pointers don't point within the same object or 
if they compare equal.

void *memmove(void *dest, const void *src, size_t n)
{
    unsigned char *pd = dest;
    const unsigned char *ps = src;
    if (__np_anyptrlt(ps, pd))
        for (pd += n, ps += n; n--;) //小技巧
            *--pd = *--ps;
    else
        while(n--)
            *pd++ = *ps++;
    return dest
}
*/

void *memmove(void *dest, const void *src, size_t n)
{
    unsigned char *pd = dest;
    const unsigned char *ps = src;
    if (ps < pd)
        for (pd += n, ps += n; n--;) //小技巧
            *--pd = *--ps;
    else
        while (n--)
            *pd++ = *ps++;
    return dest;
}

int main()
{
    char str[10] = "abcdef";
    memmove(&str[1], str, 6);
    printf("%s\n", str);
    //"bcdef",sz=6的话把最后的'\0'也move过去了
    memmove(&str[1], &str[2], 6);
    printf("%s\n", str);
    return 0;
}