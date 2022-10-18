#include <stdio.h>
#include <cs50.h>

int main(void)
{
    char a = get_char("Do you agree ?\n");
    if (a == 'y' || a == 'Y')
    {
     printf("Agreed.\n");
    }
    else if(a == 'n' || a == 'N')
    {
     printf("Not agreed.\n");
    }
    else
    {
     printf("Please just use 'y' or 'n' \n");
    }
}