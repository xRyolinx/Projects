#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("Name : ");
    printf("NAME : ");
    for (int i = 0 , n = strlen(name) ; i < n ; i++)
    {
            printf("%c", toupper(name[i]));
    }
    printf("\n");
}