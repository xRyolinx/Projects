#include <stdio.h>
#include <math.h>

//Functions' declaration
int binary(int searched , int array[] , int min , int max);

int main(void)
{
    int length = 0;
    printf("\nLength of the list : ");
    scanf("%i", &length);
    printf("\n");

    int list[length];
    for (int i = 0 ; i < length ; i++)
    {
        printf("Element %i : ", i + 1);
        scanf("%i", &list[i]);
    }

    int searched;
    printf("\nSearch : ");
    scanf("%i", &searched);

    int index = binary(searched , list , 0 , length - 1);

    if (index == -1)
    {
        printf("\nCouldn't find %i !", searched);
        return 1;
    }

    printf("\nIndex of %i is : %i\n\n", searched , index + 1);
    return 0;
}

//Functions' definition
int binary(int searched , int array[] , int min , int max)
{
    int middle = round((min + max) / 2.0);
    int array_mid = array[middle];

    if (array[middle] == searched)
    {
        return middle;
    }

    if (array[middle] != searched && (max - min) == 1)
    {
        return -1;
    }

    if (searched < array[middle])
    {
        binary(searched , array , min , middle - 1);
    }

    else if (searched > array[middle])
    {
        binary(searched , array , middle , max);
    }

}