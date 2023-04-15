#include <ctype.h>
#include "machine_abstraite.h"

//Declarations
void compile(char* text, char* parent, ptr_bloc tete);
void afficher_bloc(ptr_bloc tete);


//Definitions

//Recherche et Insertion
//Comparer caracteristiques de bloc
bool bloc_cmp(ptr_bloc ptr , char* name , char* type , char* attribut)
{
    if ((strcmp(name_bloc(ptr) , name) == 0) && (strcmp(type_bloc(ptr) , type) == 0)
         && (strcmp(attribut_bloc(ptr) , attribut) == 0))
    {
        return true;
    }
    return false;
}

//Recherche
bool recherche(ptr_bloc tete, char* name , char* type , char* attribut)
{
    ptr_bloc ptr = inside_bloc(tete);
    while(ptr != NULL)
    {
        if (bloc_cmp(ptr , name , type , attribut) == true)
        {
            return true;
        }

        ptr = suiv_bloc(ptr);
    }

    return false;
}

//Insertion (et retourne l'adresse du bloc inséré)
ptr_bloc insert(ptr_bloc tete , char* name , char* type , char* attribut)
{
    //Creer bloc
    ptr_bloc ptr = creer_bloc();

    //Caracteristiques
    modif_bloc(ptr , name , type , attribut , NULL , NULL);

    //Lier au parent
    add_inside(tete , ptr);

    //fin
    return ptr;
}



//Type classique
bool is_type(char* type)
{
    if (strcmp(type , "int") == 0 || strcmp(type , "float") == 0 || strcmp(type , "char") == 0 ||
        strcmp(type , "string") == 0 || strcmp(type , "bool") == 0 || strcmp(type , "void") == 0)
    {
        return true;
    }

    return false;
}



//Fonctions
//Return true if it's a function
bool is_fct(char* word)
{
    //Chercher parentheses
    bool check = false;

    for (int j = 0 ; word[j] != 0 ; j++)
    {
        if (word[j] == '(')
        {
            check = true;
        }
    }

    //Fin
    return check;
}

//Nom de fonction
void get_name_fct(char* string , char* name , int* k)
{
    int i = 0;

    while (string[i] != 0 && string[i] != '(')
    {
        //Copy
        name[i] = string[i];
        i++;
    }
    name[i] = 0;

    //Enlever espaces
    str_strip(name, ' ');

    //Fin
    *k = i;
}

//Create a bloc of parameter
void creer_param(ptr_bloc tete , char* string , int* index , bool* end)
{
    char declar[PARTIE];
    int i = *index;
    int j = 0;

    //Sauter la ,
    i++;

    //Declaration de parametre
    while (string[i] != ',' && string[i] != 0)
    {
        declar[j] = string[i];
        i++;
        j++;
    }
    declar[j] = 0;

    //Decomposer
    j = 0;
    char type[CARAC];
    char nom[CARAC];

    //Type
    get_word(type , declar , &j);

    //Nom
    str_rest(nom , declar , j);
    str_strip(nom , ' '); //Supprimer les espaces
    str_strip(nom , '\t'); //Supprimer les tab
    

    //Si type n'est pas vide (donc existe) , et que le nom n'est pas deja utilisé
    bool check = recherche(tete , nom , type , "parametre");
    if ((type[0] != 0) && (strcmp(type , "void") != 0) && (check == false))
    {
        //Inserer parametre
        insert(tete , nom , type , "parametre");
    }
    
    //Si arrivé a la fin de la chaine
    *end = false;
    if (string[i] == 0)
    {
        *end = true;
    }

    //Fin
    *index = i;
}

//Get function's parameters
void get_param(char* string , ptr_bloc tete)
{
    //Preparation
    int i = -1;   //Pour ne pas sauter la premiere lettre au debut dans creer_param
    ptr_bloc ptr = inside_bloc(tete);
    bool end = false;

    //Get parameters
    do
    {
        //Creer bloc de parametre et l'inserer
        creer_param(tete , string , &i , &end);
    }
    while (end == false);
}

//Compiler Fonctions
void compile_function(char* text , int* index , char* apres_type , char* type , bool* end , ptr_bloc tete)
{
    //Nom de fonction
    char name[CARAC];
    int k;
    get_name_fct(apres_type , name , &k);


    //Entrer dans les parentheses
    char entre_par[PARTIE];
    parentheses(apres_type , entre_par , &k);

    //Entrer dans le bloc local de la fonction
    //Preparation
    char entre_acc[TAILLE];
    char is_acc[PARTIE];
    str_rest(is_acc , apres_type , k);
    str_strip(is_acc , ' ');

    //Si '{' est apres la declaration de fonction , alors le bloc est juste en bas donc index est correct
    //Sinon , l'accolade ouvrante doit etre en bas
    if (strcmp(is_acc , "{") != 0)
    {
        //Trouver le {
        get_line(is_acc , text , index);
        str_strip(is_acc , ' ');
        str_strip(is_acc , '\t');
    }

    //Entrer dans les accolades
    if (strcmp(is_acc , "{") == 0)
    {
        *end = accolades(text , entre_acc , index);
    }


    //Verifier si la fonction n'existe pas deja
    bool check = recherche(tete , name , type , "fonction");
    if (check == false)
    {
        //Inserer bloc de fonction
        ptr_bloc fct = insert(tete , name , type , "fonction");

        //Inserer les Parametres
        get_param(entre_par , fct);

        //Compiler entre accolades
        compile(entre_acc , name , fct);
    }
}



//Variables
//Return name of variable
void get_name_var(char* nom , char* string , int* index , bool* end)
{
    //Copier le nom
    int i = *index;
    int j = 0;
    while (string[i] != ',' && string[i] != ';')
    {
        //Copier
        nom[j] = string[i];
        i++;
        j++;
    }
    nom[j] = 0;


    //Prochain nom
    i++;
    *index = i;

    //Fin de variables
    if (string[i] == 0)
    {
        *end = true;
    }
    else
    {
        *end = false;
    }
}

//Compiler variables
void compile_var(char* string , char* type , ptr_bloc tete)
{
    //Preparation
    str_strip(string , ' '); //Supprimer les espaces
    str_strip(string , '\t'); //Supprimer les tab
    int i = 0;
    bool end = false;

    //Get var
    do
    {
        //Nom de variable
        char nom[CARAC];
        get_name_var(nom, string , &i , &end);

        //Si variable inexistante
        bool check = recherche(tete , nom , type , "variable");
        if (check == false)
        {
            //Inserer
            insert(tete , nom , type , "variable");
        }
    }
    while (end == false);
}



//Bloc
//Compiler Bloc
void compile_bloc(char* text , int* nb_bloc , char* parent , bool* end , int* index , ptr_bloc tete)
{
    //Numero du Bloc
    (*nb_bloc)++;

    //Nom
    char name[CARAC];
    sprintf(name , "Bloc %i de %s", *nb_bloc , parent);

    //Inserer le bloc
    ptr_bloc ptr = insert(tete , name , "\0" , "\0");


    //Entrer dans les accolades
    char entre_acc[TAILLE];
    *end = accolades(text , entre_acc , index);

    //Compiler entre accolades
    compile(entre_acc , name , ptr);
}



//Affichage
//Saut de ligne
void saut_ligne(void)
{
    //Saut de ligne
    printf("|");
    print_duplic(affich - 2 , ' ');
    printf("|\n");
}

//Afficher caracteristique
void afficher_carac(char* car , int* len)
{
    if (car[0] != 0)
    {
        char string[affich];

        sprintf(string , " %s |",car);
        *len = *len + strlen(string);
        printf("%s", string);
    }
}

//Afficher nom
void afficher_nom(char* nom)
{
    char string[affich];
    sprintf(string , " Table des symboles : %s ", nom);
    print_str_center(string , '-' , affich);
}

//Afficher element
void afficher_element(ptr_bloc tete)
{
    //Si vide
    if (tete == NULL)
    {
        return;
    }

    //Debut de ligne
    saut_ligne();
    printf("|   |");

    //Preparer pour fermer le bloc a droite
    int len = 5;    // car strlen("|   |") = 5
    char string[affich];

    //Nom
    char* name = name_bloc(tete);
    afficher_carac(name , &len);
    
    //Attribut
    char* attribut = attribut_bloc(tete);
    afficher_carac(attribut , &len);
    
    //Type
    char* type = type_bloc(tete);
    afficher_carac(type , &len);

    
    //Afficher adresse
    if (inside_bloc(tete) != NULL)
    {
        sprintf(string , " Adresse : @%p |",tete);
        len = len + strlen(string);
        printf("%s", string);
    }

    //Fermer a droite
    print_duplic(affich - (len + 1) , ' ');
    printf("|\n");

    //Suivant
    afficher_element(suiv_bloc(tete));

    //Interieur
    if (inside_bloc(tete) != NULL)
    {
        //Fermer le bloc precedent en bas
        saut_ligne();
        print_str_center("" , '-' , affich);

        //Afficher nouveau bloc
        afficher_bloc(tete);
    }

    //Libérer
    free(name);
    free(type);
    free(attribut);
}

//Afficher bloc
void afficher_bloc(ptr_bloc tete)
{
    //Ouvrire le bloc
    printf("\n\n");
    char* name = name_bloc(tete);
    afficher_nom(name);
    free(name);

    //Adresse du bloc :
    //Preparer pour fermer le bloc a droite
    int len = 0;
    char string[affich];
    saut_ligne();
        
    //Debut de ligne
    printf("|");
    len++;

    //Adresse
    sprintf(string , "   Adresse : @%p", tete);
    printf("%s" , string);
    len = len + strlen(string);

    //Fermer a droite
    print_duplic((affich - 1) - len , ' ');
    printf("|\n");


    //Afficher elements du bloc
    afficher_element(inside_bloc(tete));
}




//Compilation
void compile(char* text, char* parent, ptr_bloc tete)
{
    //Analyser le code
    int i = 0;
    int nb_bloc = 0;
    bool end;
    do
    {
        //Ligne
        char ligne[PARTIE];
        end = get_line(ligne , text , &i);

        //Premier mot
        int j = 0;
        char type[CARAC];
        get_word(type , ligne , &j);
    

        //Si c'est un type
        if (is_type(type) == true)
        {
            //Reste de la ligne
            char apres_type[PARTIE];
            str_rest(apres_type , ligne , j);

            //Si fonction
            if (is_fct(apres_type) == true)
            {
                compile_function(text , &i , apres_type , type , &end , tete);
            }

            //Si variables
            else
            {
                compile_var(apres_type , type , tete);
            }
        }

        //Si Bloc
        else if (strcmp(type ,"{") == 0)
        {
            compile_bloc(text , &nb_bloc , parent , &end , &i , tete);
        }
    }
    while (end == false);
}

//Pre-compilation
void file_compile(char* chemin)
{
    //Lire le code
    char text[TAILLE];
    rdfile(chemin , text);
    printf("\n");
    print_str_center(" Code " , '-' , affich);
    printf("\n%s\n\n",text);
    print_str_center("" , '-' , affich);
    printf("\n");

    //Structure
    ptr_bloc tete = creer_bloc();
    modif_bloc(tete , "Portee globale" , "\0" , "\0" , NULL , NULL);

    //Compiler le code
    compile(text , "Portee globale" , tete);

    //Afficher les tables de symboles
    afficher_bloc(tete);
    
    //Fermer le bloc en bas
    saut_ligne();
    print_str_center("" , '-' , affich);

    //Liberer
    liberer_bloc(tete);
}
