#include <stdio.h>

//Declare premade functions
void miaw(int n);

//Main function
int main(void)
{
    miaw(3);
}

//Premade functions
void miaw(int n)
{
    for (n = 0 ; n < 3 ; n++)
    {
        printf("miaw\n");
    }
}