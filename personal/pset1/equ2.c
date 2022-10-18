#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    //Variables
    float a = get_float("a = ");
    float b = get_float("b = ");
    float c = get_float("c = ");

    float x = -c/b;

    float delta = pow(b,2)-(4*a*c);
    float x0 = (-b/(2*a));
    float x1 = (-b-sqrt(delta))/(2*a);
    float x2 = (-b+sqrt(delta))/(2*a);



    //Conditions :
    // bx + c = 0
    if (a == 0)
    {
        printf("The solution is : %.2f\n", x);
    }

    //ax^2 + bx + c
    else
    {
        if (delta == 0)
        {
            printf("The solution is : %.2f\n", x0);
        }
        else if (delta > 0)
        {
     printf("The solutions are : %s%.2f%s%.2f\n", "x1 = " , x1 , " and x2 = " , x2);
        }
        else
        {
        printf("There are no solutions for this equation.\n");
        }
    }
}