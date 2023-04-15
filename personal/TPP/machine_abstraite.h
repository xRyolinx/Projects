#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chaine.h"

#define TAILLE 1000
#define PARTIE 100
#define CARAC 50
#define affich 80

//Structure de données
//Bloc
typedef struct bloc
{
    //Caracteristiques du bloc
    char name[CARAC];
    char type[CARAC];
    char attribut[CARAC];

    //Liens
    struct bloc* inside;
    struct bloc* next;
}
bloc;
typedef bloc* ptr_bloc;



//Machines abstraites

//Creer bloc
ptr_bloc creer_bloc(void)
{
    return ((ptr_bloc) malloc(sizeof(bloc)));
}

//Caracteristiques
//Nom
char* name_bloc(ptr_bloc tete)
{
    char* tmp = malloc(sizeof(tete->name) + 1);
    strcpy(tmp , tete->name);
    return tmp;
}
//Type
char* type_bloc(ptr_bloc tete)
{
    char* tmp = malloc(sizeof(tete->type) + 1);
    strcpy(tmp , tete->type);
    return tmp;
}
//Attribut
char* attribut_bloc(ptr_bloc tete)
{
    char* tmp = malloc(sizeof(tete->attribut) + 1);
    strcpy(tmp , tete->attribut);
    return tmp;
}
//Inside
ptr_bloc inside_bloc(ptr_bloc tete)
{
    return tete->inside;
}
//Suivant
ptr_bloc suiv_bloc(ptr_bloc tete)
{
    return tete->next;
}

//Affectations
//Nom
void aff_nom_bloc(ptr_bloc tete , char* nom)
{
    strcpy(tete->name , nom);
}
//Type
void aff_type_bloc(ptr_bloc tete , char* type)
{
    strcpy(tete->type , type);
}
//Attribut
void aff_attribut_bloc(ptr_bloc tete , char* attribut)
{
    strcpy(tete->attribut , attribut);
}
//Inside
void aff_inside_bloc(ptr_bloc tete , ptr_bloc inside)
{
    tete->inside = inside;
}
//Suivant
void aff_suiv_bloc(ptr_bloc tete , ptr_bloc suivant)
{
    tete->next = suivant;
}
//Modifier bloc
void modif_bloc(ptr_bloc tete , char* name , char* type , char* attribut , ptr_bloc inside , ptr_bloc next)
{
    strcpy(tete->name , name);
    strcpy(tete->type , type);
    strcpy(tete->attribut , attribut);
    tete->inside = inside;
    tete->next = next;
}



//Liberer Blocs
void liberer_bloc(ptr_bloc tete)
{
    //Si vide
    if (tete == NULL)
    {
        return;
    }

    //Liberer l'interieur
    liberer_bloc(tete->inside);
    
    //Liberer les suivants
    liberer_bloc(tete->next);

    //Liberer la tete
    free(tete);
}



//Dernier pointeur
ptr_bloc last_ptr(ptr_bloc ptr)
{
    //Si vide
    if (ptr == NULL)
    {
        return NULL;
    }

    //Aller au dernier pointeur
    while(ptr->next != NULL)
    {
        ptr = ptr->next;
    }

    //Fin
    return ptr;
}

//Ajouter a la fin
void add_next(ptr_bloc ptr , ptr_bloc add)
{
    //Arriver a la fin
    ptr = last_ptr(ptr);
    
    //Ajouter
    ptr->next = add;
}

//Ajouter dedans
void add_inside(ptr_bloc ptr , ptr_bloc add)
{
    //Si contenu vide
    if (ptr->inside == NULL)
    {
        ptr->inside = add;
    }
    //Si non vide
    else
    {
        add_next(ptr->inside , add);
    }
}
