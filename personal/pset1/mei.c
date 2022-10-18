#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Variables
    float x = 0;

    //Nombre de fois
    do
    {

        if (x < 0)
        {
            printf("Ecris un nombre positif seulement !\n");
        }
        x = get_int("Combien de fois aimes-tu ta moitié ? ");
    }
    while (x < 0);

    //Afficher
    if (x == 0)
    {
        printf("Je l'aime 0 fois\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("Non je rigole ...\n");
        printf("Je l'aime a l'infini !\n");
    }
    else if (x < 10)
    {
        printf("je l'aime %.0f fois seulement ...\n", x);
    }
    else if (x > 9 && x < 100)
    {
        printf("je l'aime %.0f fois .\n", x);
    }
    else if (x > 99 && x < 1000)
    {
        printf("je l'aime %.0f fois !\n", x);
    }
    else if (x > 999 && x < 10000)
    {
        printf("je l'aime %.0f fois !!\n", x);
    }
    else
    {
        printf("je l'aime %.0f fois !!!\n", x);
    }
}