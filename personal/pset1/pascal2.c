#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    //Variables
    float a = get_float("a = ");
    float b = get_float("b = ");
    float z = pow(a, 2) + pow(b, 2) + 2 * a * b;

    //Result
    printf("(%.2f%s%.2f%s%.2f\n", a, " + ", b, ")^2 = ", z);
}