#include <stdio.h>
#include <cs50.h>

char z;

int main(void)
{
    printf("What do you want to do ? \n");

    do
    {
        z = get_char("Please choose a for addition , s for substraction , m for multiplication or d for division \n");
    }
    while(z != 'a' && z != 's' && z != 'm' && z != 'd');

    float x = get_float("x = ");
    float y = get_float("y = ");
    if(z == 'a')
    {
        printf("%.2f\n", x + y);
    }
    if(z == 's')
    {
        printf("%.2f\n", x - y);
    }
    if(z == 'm')
    {
        printf("%.2f\n", x*y);
    }
    if(z == 'd')
    {
        printf("%.2f\n", x/y);
    }
    return 0;
}