#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int points = get_int("how many points did you lose ?\n");

    if(points>2)
    {
        printf("You lost more points than me\n");
    }
    else
    {
        if(points<2)
        {
            printf("You lost less points than me\n");
        }
        else
        {
            printf("You lost as many points as me\n");
        }
    }
}