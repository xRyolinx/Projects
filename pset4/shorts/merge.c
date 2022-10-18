#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Functions declaration
void sort(int min , int max , int list[]);

//Start
int main(void)
{
    //Getting the length of the list
    int number;
    printf("How many number : ");
    scanf("%i", &number);

    //Getting the numbers of the list
    int list[number];
    for (int i = 0 ; i < number ; i++)
    {
        printf("Number %i : ", i + 1);
        scanf("%i", &list[i]);
    }

    //Entered list
    printf("\nEntered list :");
    for (int i = 0 ; i < number - 1 ; i++)
    {
        printf(" %i ,", list[i]);
    }
    printf(" %i .\n", list[number - 1]);

    //Sorting the list
    sort(0 , number , list);

    //Printing the list
    printf("Sorted list :");
    for (int i = 0 ; i < number - 1 ; i++)
    {
        printf(" %i ,", list[i]);
    }
    printf(" %i .\n", list[number - 1]);

    //Ending programme
    return 0;
}

//Functions definition
void sort(int min , int max , int list[])
{
    int size = max - min;
    if (size > 1)
    {
        //First half
        int size1 = round(size / 2);
        int half_1[size1];

        for (int i = 0 ; i < size1 ; i++)
        {
            half_1[i] = list[i];
        }

        //Second half
        int size2 = size - size1;
        int half_2[size2];

        for (int i = size1 ; i < size ; i++)
        {
            half_2[i - size1] = list[i];
        }

        //Sort the 2 halves
        sort(min , round ((min + max) / 2) , half_1);
        sort(round ((min + max) / 2) , max , half_2);

        //Merge the 2 halves
        int x = 0;
        int y = 0;
        int z = 0;

        while (z != size)
        {
            //If both lists still have numbers
            if (x < size1 && y < size2)
            {
                if (half_1[x] < half_2[y])
                {
                    list[z] = half_1[x];
                    x++;
                    z++;
                }
                else
                {
                    list[z] = half_2[y];
                    y++;
                    z++;
                }
            }

            //If the first list is finished
            else if(x == size1)
            {
                list[z] = half_2[y];
                y++;
                z++;
            }

            //If the second list is finished
            else
            {
                list[z] = half_1[x];
                x++;
                z++;
            }
        }

    }
}