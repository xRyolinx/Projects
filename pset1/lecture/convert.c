#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    float euro = get_float("Euro : ");
    int dz = round(euro * 200);
    printf("Dz : %i\n", dz);
}