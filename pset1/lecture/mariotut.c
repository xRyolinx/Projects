#include <stdio.h>
#include <cs50.h>

int n;
int main(void)
{
    do
    {
        n = get_int("Size : ");
    }
    while (n < 1);

    //For collumns
    for ( int i = 0 ; i < n ; i++)
    {

        //For rows
        for(int j = 0 ; j < n ; j++)
        {

        //Make brick
        printf("# ");
        }

    //Move to new line
    printf("\n");
    }
}