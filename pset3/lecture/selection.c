#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int numbers[] = {5 , 2 , 7 , 4 , 1 , 6 , 3 , 0};
    int min;
    int temp;

    printf("Sorted numbers :");

    for (int i = 0 ; i < 8 ; i++)
    {
        min = i;

        for (int j = i ; j < 8 ; j++)
        {
            if (numbers[min] >= numbers[j])
            {
                min = j;
            }
        }

        temp = numbers[i];
        numbers[i] = numbers[min];
        numbers[min] = temp;

        printf(" %i", numbers[i]);
    }

    printf("\n");
}