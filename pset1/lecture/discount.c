#include <stdio.h>
#include <cs50.h>
#include <math.h>

//Declare premade functions
float discount(float price , float percentage);

//Main function
int main(void)
{
    float price = get_float("The price : ");
    float percentage = get_float("The percentage off : ");
    float sale = round(discount(price , percentage));
    printf("TTC : %.2f\n", sale);
}

//Premade functions
float discount(float price , float percentage)
{
    return price*((100-percentage)/100);
}