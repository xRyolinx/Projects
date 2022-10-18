#include <stdio.h>
#include <cs50.h>

//Function declaration
int collatz(int n);

int main(void)
{
    int number = get_int("Number : ");
    int steps = collatz(number);
    printf("Steps : %i\n", steps);
}

//Function definition
int collatz(int n)
{
    if (n == 1)
    {
        return 0;
    }

    else
    {

        if (n % 2 == 0)
        {
            return 1 + collatz(n / 2);
        }

        else
        {
            return 1 + collatz(3 * n + 1);
        }

    }
}