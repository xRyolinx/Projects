#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int numbers[] = {4 , 6 , 8 , 9 , 1 , 2 , 0};

    for(int i = 0 ; i < 7 ; i++)
    {
        if (numbers[i] == 0)
        {
            printf("Found\n");
            return 0;
        }
    }

    printf("Not found\n");
    return 1;
}