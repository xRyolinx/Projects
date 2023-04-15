#include <stdio.h>
#include <stdbool.h>

//Fonctions
//Strip character from string
void str_strip(char* string , char c)
{
    //Iterate over all the chars
    for (int i = 0 ; string[i] != 0 ; i++)
    {
        if (string[i] == c)
        {
            //Strip the char
            for (int j = i ; string[j] != 0 ; j++)
            {
                string[j] = string[j + 1];
            }

            //Revoir la valeur d'apres
            i--;
        }
    }
}

//Get rest of string (from index to end of string)
void str_rest(char* rest , char* ligne , int index)
{
    int j = 0;
    //Copy
    for (int i = index ; ligne[i] != 0 ; i++ , j++)
    {
        rest[j] = ligne[i];
    }
    rest[j] = 0;
}

//Afficher une chaine 'text' , coincée entre des caracteres 'c' , où le total a une longueur 'length'
void print_str_center(char* text , char c , int length)
{
    int len = strlen(text);
    int bef = (length - len) / 2;
    int aft = length - (bef + len);

    for (int i = 0 ; i < bef ; i++)
    {
        printf("%c", c);
    }

    printf("%s",text);

    for (int i = 0 ; i < aft ; i++)
    {
        printf("%c", c);
    }
    printf("\n");
}

//Dupliquer un caractere et afficher
void print_duplic(int nb , char c)
{
    for (int i = 0 ; i < nb ; i++)
    {
        printf("%c" , c);
    }
}



//Read file in a string
void rdfile(char* chemin , char* text)
{
    int i = 0;
    FILE* fichier = fopen(chemin , "r");
    char c;
    while (true)
    {
        //Lire caractere
        c = fgetc(fichier);

        //Si fin de fichier
        if (c == EOF)
            break;

        //Copier
        text[i] = c;
        i++;
    }
    text[i] = 0;

    //End
    fclose(fichier);
}

//Get line and return true if end of text
bool get_line(char* line , char* text , int* index)
{
    int i = *index;

    //Sauter les \n avant
    while (text[i] == '\n')
    {
        i++;
    }

    //Copy line
    int j;
    for (j = 0 ; text[i] != '\n' && text[i] != 0 ; i++ , j++)
    {
        line[j] = text[i];
    }

    //Sauter les espaces apres pour savoir si on est arrivé a la fin
    while (text[i] == '\n')
    {
        i++;
    }
    *index = i;
    
    //Finish line
    line[j] = 0;

    //If end of text
    if (text[i] == 0)
    {
        return true;
    }
    
    //End
    return false;
}

//Get word and return true if end of line
bool get_word(char* word , char* line , int* index)
{
    //Copy line
    int i = *index;
    int j;
    //Sauter les espaces avant
    while (line[i] == ' ' || line[i] == '\t')
    {
        i++;
    }
    //Copy word
    for (j = 0 ; line[i] != ' ' && line[i] != 0 ; i++ , j++)
    {
        word[j] = line[i];
    }
    //Sauter les espaces apres pour savoir si on est arrivé a la fin
    while (line[i] == ' ' || line[i] == '\t')
    {
        i++;
    }
    
    //Finish word
    *index = i;
    word[j] = 0;


    //If end of line
    if (line[i] == 0)
    {
        return true;
    }

    //End
    return false;
}



//Copier ce qu'il ya entre parentheses
void parentheses(char* string , char* buffer , int* index)
{
    int count = 0;
    int i = *index;
    int j = 0;

    //Get inside parentheses
    i++;

    //Copy string inside parentheses
    while(string[i] != ')' || count != 0)
    {
        //Copy
        buffer[j] = string[i];

        //New parentheses
        if (buffer[j] == '(')
        {
            count++;
        }
        if (buffer[j] == ')')
        {
            count--;
        }

        //Fin
        i++;
        j++;
    }
    buffer[j] = 0;

    //Apres )
    i++;
    *index = i;
}

//Copier ce qu'il ya entre accolades , et retourne true si arriver a la fin de la chaine
bool accolades(char* string , char* buffer , int* index)
{
    int count = 0;
    int i = *index;
    int j = 0;

    //Sauter les \n ou espace avant
    while (string[i] == '\n' || string[i] == ' ')
    {
        i++;
    }


    //Copy string inside accolades
    while (string[i] != '}' || count != 0)
    {
        //Copy
        buffer[j] = string[i];

        //New accolades
        if (buffer[j] == '{')
        {
            count++;
        }
        if (buffer[j] == '}')
        {
            count--;
        }

        //Fin
        i++;
        j++;
    }
    buffer[j] = 0;

    //Sortir des }
    i++;
    *index = i;

    //Sauter les \n ou espace apres
    while (string[i] == '\n' || string[i] == ' ')
    {
        i++;
    }

    //Si arriver a la fin
    if (string[i] == 0)
    {
        return true;
    }

    //Fin
    return false;
}
