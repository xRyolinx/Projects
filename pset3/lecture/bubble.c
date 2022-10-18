#include <stdio.h>

int main(void)
{
    //Getting the length of the list
    int number;
    printf("How many number : ");
    scanf("%i", &number);

    //Getting the numbers of the list
    int numbers[number];
    for (int i = 0 ; i < number ; i++)
    {
        printf("Number %i : ", i + 1);
        scanf("%i", &numbers[i]);
    }

    //Entered list
    printf("\nEntered list :");
    for (int i = 0 ; i < number - 1 ; i++)
    {
        printf(" %i ,", numbers[i]);
    }
    printf(" %i .\n", numbers[number - 1]);

 
    printf("Number : ");

    for (int j = 0 ; j < number ; j++)
    {
        int total = 0;

        for (int i = 0 ; i < number ; i++)
        {
            int temp;

            if (numbers[i] >= numbers[i + 1])
            {
                temp = numbers[i];
                numbers[i] = numbers[i + 1];
                numbers[i + 1] = temp;
            }
            else
            {
                total += 1;
            }
        }

        if (total == 0)
        {
            break;
        }
    }

    for (int j = 0 ; j < number ; j++)
    {
    printf(" %i ,", numbers[j]);
    }

    printf("\n");
}