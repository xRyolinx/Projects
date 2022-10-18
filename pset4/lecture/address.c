#include <stdio.h>

int main(void)
{
    int n = 50;
    int *p = &n;
    char *s = "Hehe";
    printf("%p\n", p);
    printf("%i\n", *p);
    printf("%c\n", s[0]);
}