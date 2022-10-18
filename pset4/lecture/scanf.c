#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *s = malloc(4);
    printf("s : ");
    scanf("%s", s);
    printf("Entered : %s\n", s);
}