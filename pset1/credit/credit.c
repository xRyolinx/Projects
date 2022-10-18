//Libraries
#include <cs50.h>
#include <stdio.h>
#include <math.h>

//Variables
long long int number;

//Declaring functions
int numofdig(long long int x);
int digit(int x);
int digadd(int x);

//Start Luhn's algorithm
int main(void)
{
    //Insert nummber and confirming it
    do
    {
        number = get_long("Number : ");
    }
    while (number < 0);

    //Variables
    int num = numofdig(number);
    int total1 = 0;
    int total2 = 0;

    //Total 1 of digits
    for (int n = num - 1 ; n > 0 ; n -= 2)
    {
        int dig = digit(n);
        int add = digadd(dig);
        total1 += add;
    }

    //Total 2 of digits
    for (int n = num ; n > 0 ; n -= 2)
    {
        int dig = digit(n);
        total2 = total2 + dig;
    }

    //Total
    int total = total1 + total2;

    //Checking validity
    int check = total % 10;
    if (check != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        if (num == 15 && digit(1) == 3 && (digit(2) == 4 || digit(2) == 7))
        {
            printf("AMEX\n");
        }
        else if ((num == 13 || num == 16) && digit(1) == 4)
        {
            printf("VISA\n");
        }
        else if (num == 16 && digit(1) == 5 && (digit(2) == 1 || digit(2) == 2 || digit(2) == 3 || digit(2) == 4 || digit(2) == 5))
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

}


//Premade Functions

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
int digit(int x)
{
    int num = numofdig(number);
    long long int dig10 = pow(10, (num - x));
    long long int befdig = (number - (number % dig10)) / dig10 ;
    int digit = befdig % 10;
    return digit;
}

//Addition of digits of digits
int digadd(int x)
{
    int add = 2 * x;
    int dig_st = add % 10;
    int dig_nd = (add - dig_st) / 10 ;
    return dig_st + dig_nd;
}
