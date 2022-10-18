#include <stdio.h>
#include <cs50.h>
#include <math.h>

//Data structures
typedef struct
{
    int num;
    int numdig;
    int digit[18];
}
number;

typedef struct
{
    int num;
    int number[10];
}
numeral;

//Declare functions
int numofdig(long long int x);
int digit(long long int a , int b , int c);
bool check(int x , int array[]);


//Start
int main(void)
{
    //Getting how many number the list has
    printf("\nHow many number does your list contain ?\n");
    int numofnumb = get_int("Number of the list's components : ");
    printf("\n");

    //Getting the numbers of the list
    number numbers[numofnumb];
    for (int i = 0 ; i < numofnumb ; i++)
    {
        numbers[i].num = get_int("Number %i : ", i + 1);
    }
    printf("\n");

    //Printing the list
    printf("The list entered :");
    for (int i = 0 ; i < numofnumb - 1 ; i++)
    {
        printf(" %i ", numbers[i].num);
    }
    printf(" %i .\n", numbers[numofnumb - 1].num);
    printf("\n");

    //Getting the number of digits of each number
    for (int i = 0 ; i < numofnumb ; i++)
    {
        numbers[i].numdig = numofdig(numbers[i].num);
    }

    //Getting the digit of each number
    for (int i = 0 ; i < numofnumb ; i++)
    {
        for (int j = 0 ; j < numbers[i].numdig ; j++)
        {
            numbers[i].digit[j] = digit(numbers[i].num , numbers[i].numdig , j + 1);
        }
    }

    numeral numerals[9];
    //Getting the numbers composed of same digit
    for (int i = 0 ; i < 9 ; i++)
    {
        numerals[i].num = 0;
        for (int j = 0 ; j < numofnumb ; j++)
        {
            bool x = check(numbers[j].numdig , numbers[j].digit);
            if (x == true && numbers[j].digit[0] == i + 1)
            {
                numerals[i].number[numerals[i].num] = numbers[j].num;
                numerals[i].num++;
            }
        }
    }

    //Printing the digits repeated
    printf("The digits repeated are : ");
    for (int i = 0 ; i < 9 ; i++)
    {
        if (numerals[i].num > 0)
        {
            printf(" %i .", i + 1);
        }
    }
    printf("\n\n");

    //Printing the numbers composed of the same digits
    printf("The numbers :\n");
    for (int i = 0 ; i < 9 ; i++)
    {
        if (numerals[i].num > 0)
        {
            printf("Number %i :", i + 1);

            for (int j = 0 ; j < numerals[i].num ; j++)
            {
                printf(" %i .", numerals[i].number[j]);
            }
            printf("\n");
        }
    }
    printf("\n");

}

//Number of digits
int numofdig(long long int x)
{
    int num = 0;
    long long int q = 10;
    while (q >= 10)
    {
        q = x / pow(10, num);
        num++;
    }
    return num;
}

//Digit
int digit(long long int a , int b , int c)
{
    long long int dig10 = pow(10, (b - c));
    long long int befdig = (a - (a % dig10)) / dig10 ;
    int digit = befdig % 10;
    return digit;
}

//Check
bool check(int x , int array[])
{
    for (int i = 0 ; i < x - 1 ; i++)
    {
        if (array[i] != array[i + 1])
        {
            return false;
        }
    }

    return true;
}
