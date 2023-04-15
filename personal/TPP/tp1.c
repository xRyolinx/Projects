#include "tp1_lib.h"

int main(void)
{
    while(true)
    {
        //text
        char chemin[CARAC];
        printf("\n\n");
        print_str_center(" Menu " , '-' , affich);

        printf("\nEntrez le chemin du fichier (ou Q pour quitter)\nInput : ");
        fgets(chemin , TAILLE , stdin);
        str_strip(chemin , '\n');

        //Quitter
        if (strcmp(chemin , "q") == 0 || strcmp(chemin , "Q") == 0)
        {
            break;
        }

        //Compile
        file_compile(chemin);

        //Espacer
        printf("\n");
    }

    //Fin
    printf("\n");
}