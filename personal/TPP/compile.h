#include "machine_abstraite.h"

//!   LIBRARIE NON UTILISÉE DANS LE TP   !//

//File d'Attente de Compilation
typedef struct maillon_fi
{
    //Caracteristiques
    char text[TAILLE];
    char parent[CARAC];
    ptr_bloc tete;

    //Suivant
    struct maillon_fi* suivant;
}
maillon_fi;
typedef maillon_fi* ptr_fi;


//Machines abstraites
//Text
char* text_fi(ptr_fi ptr)
{
    char* tmp = (char*)malloc(sizeof(ptr->text) + 1);
    strcmp(tmp , ptr->text);
    return tmp;
}
//Nom du parent
char* parent_fi(ptr_fi ptr)
{
    char* tmp = (char*)malloc(sizeof(ptr->parent) + 1);
    strcmp(tmp , ptr->parent);
    return tmp;
}
//Tete
ptr_bloc tete_fi(ptr_fi ptr)
{
    return ptr->tete;
}
//Suiv
ptr_fi suiv_fi(ptr_fi ptr)
{
    return ptr->suivant;
}

//Affectations
//Text
void aff_text_fi(ptr_fi ptr , char* text)
{
    strcpy(ptr->text , text);
}
//Parent
void aff_parent_fi(ptr_fi ptr , char* parent)
{
    strcpy(ptr->parent , parent);
}
//Tete
void aff_tete_fi(ptr_fi ptr , ptr_bloc tete)
{
    ptr->tete = tete;
}
//Suivant
void aff_suiv_fi(ptr_fi ptr , ptr_fi suiv)
{
    ptr->suivant = suiv;
}
//Modifier
void modifier_fi(ptr_fi ptr , char* text , char* parent , ptr_bloc tete , ptr_fi suiv)
{
    strcpy(ptr->text , text);
    strcpy(ptr->parent , parent);
    ptr->tete = tete;
    ptr->suivant = suiv;
}


//Creer file
ptr_fi creer_maillon_fi()
{
    return ((ptr_fi) malloc(sizeof(maillon_fi)));
}

//Ajouter file
void enfiler(ptr_fi* tete , ptr_fi add)
{
    //Si vide
    if (*tete == NULL)
    {
        *tete = add;
    }
    //Sinon
    else
    {
        ptr_fi tmp = *tete;
        //Aller a la fin de la liste
        while(tmp->suivant != NULL)
        {
            tmp = suiv_fi(tmp);
        }
        //Enfiler
        aff_suiv_fi(tmp , add);
    }
}

void defiler(ptr_fi* tete)
{
    ptr_fi tmp = *tete;
    *tete = (*tete)->suivant;
    free(tmp);
}

bool file_vide(ptr_fi tete)
{
    if (tete == NULL)
    {
        return true;
    }
    return false;
}