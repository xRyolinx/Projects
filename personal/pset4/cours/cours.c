#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Functions declaration
int check(int number , char* input , char* students[]);
int search(char* eleve , char* students[] , int number);
void modify(char* reader , FILE* modi);
int strfinder(char* found , char* list , int start , int stop);
void makeplace(int index , int places , char* reader);
void delplace(int index , int space , char* reader);
int confirmation(void);
void addseance(char* seance , char* reader , FILE* modi , int seance_paie);
void convert(int num , char* numstring);
void delseance(char* reader , FILE* modi , int start , int end , int seance_paie);
void modseance(char* reader , FILE* modi , int start , int end , int seance_paie);
int checkdate(char* date);
int checkhour(char* hours);
void askeleve(char* eleve , char* name);
void addeleve(char* eleve , char* name , int number);
void updatepaie(char* reader , int add , FILE* modi);


//Start
int main(void)
{
    while(1)
    {
        
        //Enter or quit
        char* entry = malloc(2);
        entry[0] = 'E';
        entry[1] = '\0';
        do
        {
            if (strcmp(entry , "E") != 0 && strcmp(entry , "Q") != 0)
            {
                printf("\n\nEntrez 'e' ou 'q' seulement !\n");
            }

            printf("\nEntrez 'e' pour Entrer\nEntrez 'q' pour Quitter\nReponse : ");
            scanf("%s", entry);
            entry[0] = toupper(entry[0]);
            entry[1] = '\0';
        }
        while (strcmp(entry , "E") != 0 && strcmp(entry , "Q") != 0);

        //Quit
        if (strcmp(entry , "Q") == 0)
        {
            free(entry);

            break;
        }
        free(entry);


        //Acccessing data base
        //Getting number of students

        FILE* nb = fopen("data/nombre.txt", "r");
        int number;
        fread(&number , sizeof(int) , 1 , nb);

        //Reading students file
        FILE* std = fopen("data/eleves.txt", "r");
        char* students[number];

        for(int i = 0 ; i < number ; i++)
        {
            students[i] = malloc (20);
        }

        printf("\n\nListe d'eleves :\n\n");
        for (int i = 0 ; i < number ; i++)
        {
            int j = -1;
            int z = 0;

            char* read = malloc(30);
            read[0] = 'r';

            while (read[z] != 10)
            {
                j++;
                read[j] = fgetc(std);
                z = j;
            }

            read[j] = '\0';

            strcpy(students[i] , read);
            free(read);

            printf("Eleve %i : %s\n", i + 1 , students[i]);
        }

        //Asking for task
        char* task = malloc(20);
        strcpy(task , "A");
        printf("\nQue voulez-vous faire ?\n");
        getchar();

        do
        {
            if (strlen(task) != 1 || (task[0] != 'A' && task[0] != 'I'))
            {
                printf("\n");
            }

            if (strlen(task) != 1)
            {
                printf("La reponse doit contenir 1 caractere seulement !\n");
            }

            if (task[0] != 'A' && task[0] != 'I')
            {
                printf("Choisissez entre 'a' ou 'i' seulement !\n");
            }

            printf("Entrez :\n'a' pour acceder aux informations des eleves");
            printf("\n'i' pour inscrire un eleve\n\nReponse : ");

            fgets(task , 20 , stdin);
            task[0] = toupper(task[0]);
            task[1] = '\0';
        }
        while (strlen(task) != 1 || (task[0] != 'A' && task[0] != 'I'));

        //Name of student and his file
        char* eleve = malloc(30);
        char* name = malloc(40);
        strcpy(eleve , "a");


        //Differentiate between signed-in and old students
        int inscri = 2;
        int sinscri = 0;

        if (task[0] == 'I')
        {
            sinscri = 1;

            //Getting student's name and file
            askeleve(eleve , name);

            //Add student to data base
            addeleve(eleve , name , number);
        }

        else if (task[0] == 'A')
        {
            //Getting student's name and file
            askeleve(eleve , name);
            
            //Comparing input with database
            int result = check(number , eleve , students);

            if (result == 0)
        {
            printf("L'eleve n'est pas inscrit ! Voulez vous l'ajouter ?\n");
            inscri = confirmation();

            if (inscri == 1)
            {
                sinscri = 1;

                //Add student to data base
                addeleve(eleve , name , number);
            }
            else
            {
                printf("\n%s n'a pas ete inscrit !\n", eleve);
            }
        }

        }


        char* rep = malloc(5); 
        if (inscri != 0)
        {
            strcpy(rep , "L");
            do
            {
            //Accessing student file
            if (strlen(rep) != 1 || (rep[0] != 'L' && rep[0] != 'M' && rep[0] != 'R'))
            {
                printf("\n");
            }
            if (strlen(rep) != 1)
            {
                printf("La reponse doit comporter un caractere seulement !\n");
            }
            if (rep[0] != 'L' && rep[0] != 'M' && rep[0] != 'R')
            {
                printf("Choisissez seulement entre 'l' , 'm' ou 'r' !\n");
            }

            printf("\nQue voulez vous faire ?\nChoisissez entre :\n'l' pour Lire\n");
            printf("'m' pour Modifier\n'r' pour Retirer\n\nReponse : ");
            scanf("%s", rep);
            rep[0] = toupper(rep[0]);
            }
            while(strlen(rep) != 1 || (rep[0] != 'L' && rep[0] != 'M' && rep[0] != 'R'));
        }

        if (rep[0] == 'R' && inscri != 0)
        {
            free(rep);

            printf("\nVoulez-vous vraiment retirer %s ?", eleve);

            int rep = confirmation();

            if (rep == 0)
            {
                printf("\nOperation annulee : l'eleve n'a pas ete retire !\n");
            }
            if (rep == -1)
            {
                printf("\nCommande invalide !");
            }

            //Getting the index of the wanted student;
            int removed = search(eleve , students , number);

            if (removed == -1)
            {
                printf("\nEleve introuvable !");
            }

            //Sorting the array
            for (int i = removed ; i < number - 1 ; i++)
            {
                students[i] = students[i + 1];
            }
    
            //Modify numbers
            number--;
            FILE* addnm = fopen("data/nombre.txt" , "w");
            fwrite(&number , sizeof(int) , 1 , addnm);
            fclose(addnm);


            //Modify names
            FILE* addname = fopen("data/eleves.txt" , "w");
            for (int i = 0 ; i < number ; i++)
            {
                fwrite(students[i] , sizeof(char) , strlen(students[i])  , addname);
                fputc(10 , addname);
            }
            fclose(addname);

            printf("\n%s a ete retire avec succes !\n\n", eleve);

            //Deleting student's file
            printf("Voulez-vous supprimer egalement le fichier de %s ?", eleve);
            int confirm;
            do
            {
                confirm = confirmation();
            }
            while (confirm == -1);

            if (confirm == 0)
            {
                printf("\nLe fichier a ete preserve\n");
            }
            else
            {
                int delete = remove(name);

                if (delete == 0)
                {
                    printf("\nLe fichier a bien ete supprime !\n");
                }
                else
                {
                    printf("\nFichier introuvable\n");
                }
            }
        }


        else if ((rep[0] == 'L' || rep[0] == 'M') && inscri != 0)
        {
            int modif = 0;
            if (rep[0] == 'M')
            {
                modif = 1;
            }

            free(rep);

            FILE* elefile = fopen(name , "r");
            char* reader = malloc(1000);

            fseek(elefile , 0 , SEEK_END);
            int end = ftell(elefile);
            fseek(elefile , 0 , SEEK_SET);
        
            fread(reader , 1 , end , elefile);
            printf("\n\n%s", reader);
        
            fclose(elefile);

            if (modif == 0)
            {
                free(reader);
            }

            if (modif == 1)
            {
                FILE* modi = fopen(name , "w");
                modify(reader , modi);

                printf("\nModification terminee :\n\n%s", reader);
                fclose(modi);
                free(reader);
            }
        }

        //End programme
        printf("\nAppuyez sur Entrer pour terminer : ");
        char* fini = malloc(2);
        getchar();
        fgets(fini , 2 , stdin);
        free(fini);
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

        fclose(nb);
        fclose(std);
        
        for (int i = 0 ; i < number - sinscri ; i++)
        {
           free(students[i]);
        }

        free(eleve);
        free(name);
    }

    return 0;
}

//Functions definition
int check(int number , char* input , char* students[])
{
    for (int i = 0 ; i < number ; i++)
        {
            if (strcmp(input , students[i]) == 0)
            {
                return 1;
            }
        }

    return 0;
}

int search(char* eleve , char* students[] , int number)
{
    for (int i = 0 ; i < number ; i++)
    {
        if (strcmp(eleve , students[i]) == 0)
        {
            return i;
        }
    }

    return -1;
}

void modify(char* reader , FILE* modi)
{
    printf("\n\nQue voulez-vous modifier ?\n");
    printf("Choissez :\n't' pour type\n'se' pour seances effectues\n");
    printf("'sr'pour seances ratees\n'p' pour paiement\n");
    printf("\nReponse : ");
    char* rep = malloc(3);
    scanf("%s", rep);

    if (strcmp(rep , "t") == 0)
    {
        free(rep);
        int index = strfinder("Type : " , reader , 0 , strlen(reader));
        int check1 = strfinder("Individuel" , reader , 0 , strlen(reader));
        int check2 = strfinder("Groupe" , reader , 0 , strlen(reader));

        if (check1 != -1)
        {
            printf("Cet eleve fait des cours individuels\n");
            printf("Voulez-vous le mettre en Groupe ?\n");

            int rep = confirmation();
            if (rep == 0)
            {
                printf("Operation annulee\n");
            }
            else if (rep == -1)
            {
                printf("Repondez seulement par oui ou non !\n");
            }

            else
            {
                char* grppp = malloc(5);
                strcmp(grppp , "A");
                do
                {
                    if (strlen(grppp) != 1 || isalnum(grppp[0]) == 0)
                    {
                        printf("\n");
                    }
                    if (strlen(grppp) != 1)
                    {
                        printf("La reponse ne doit contenir qu'un caractere !\n");
                    }
                    if (isalnum(grppp[0]) == 0)
                    {
                        printf("Choisissez entre un chiffre ou une lettre seulement !\n");
                    }

                    printf("\nDans quel groupe l'integrer ?\nEntrez le chiffre ou la lettre correspondant(e) : ");
                    scanf("%s", grppp);
                    grppp[0] = toupper(grppp[0]);
                }
                while (strlen(grppp) != 1 || isalnum(grppp[0]) == 0);

                int indexadd = index + strlen("Type : ");
                delplace(indexadd , strlen("Individuel") - strlen("Groupe X") , reader);

                //Updating the reader
                char groupe[9] = "Groupe X";
                groupe[7] = grppp[0];
                for (int i = 0 ; i < strlen("Groupe X") ; i++)
                {
                    reader[indexadd + i] = groupe[i];
                }
                free(grppp);

                //Updating the file
                fwrite(reader , sizeof(char) , strlen(reader) , modi);

                printf("\n\nFichier modifie avec succes !");
            }
        }

        if (check2 != -1)
        {
            printf("\nL'eleve fait partie du Groupe %c\n", reader[index + strlen("Type : Groupe ")]);
            printf("Que voulez-vous faire ?\n");
            printf("\nChoisissez :\n'i' pour le changer en Individuel\n'g' pour changer de Groupe\n");

            char* repp = malloc(5);
            strcpy(repp , "I");
            do
            {
                if (strlen(repp) != 1 || (repp[0] != 'I' && repp[0] != 'G'))
                {
                    printf("\n");
                }
                if (strlen(repp) != 1)
                {
                    printf("La reponse ne doit contenir qu'un caractere !\n");
                }
                if (repp[0] != 'I' && repp[0] != 'G')
                {
                    printf("Choisissez entre 'I' ou 'G' seulement !\n");
                }

                printf("\nReponse : ");
                scanf("%s", repp);
                repp[0] = toupper(repp[0]);
            }
            while (strlen(repp) != 1 || (repp[0] != 'I' && repp[0] != 'G'));

            if (repp[0] == 'I')
            {
                printf("Voulez-vous vraiment le changer en Individuel ?");

                int rep = confirmation();
                if (rep == 0)
                {
                    printf("Operation annulee\n");
                }
                else if (rep == -1)
                {
                    printf("Repondez seulement par oui ou non !\n");
                }
                else
                {
                    int indexadd = index + strlen("Type : ");
                    makeplace(indexadd , strlen("Individuel") - strlen("Groupe X") , reader);

                    //Updating the reader
                    char indiv[11] = "Individuel";
                    for (int i = 0 ; i < strlen("Individuel") ; i++)
                    {
                        reader[indexadd + i] = indiv[i];
                    }

                    //Updating the file
                    fwrite(reader , sizeof(char) , strlen(reader) , modi);

                    printf("\nFichier modifie avec succes !");
                }
            }

            else if (repp[0] == 'G')
            {
                char grp[5];
                strcpy(grp , "A");
                do
                {
                    if (strlen(grp) != 1 || isalnum(grp[0]) == 0)
                    {
                        printf("\n");
                    }
                    if(strlen(grp) != 1)
                    {
                        printf("La reponse ne doit contenir qu'un caractere !\n");
                    }
                    if (isalnum(grp[0]) == 0)
                    {
                        printf("Choisissez entre un chiffre ou une lettre seulement !\n");
                    }

                    printf("\nDans quel groupe l'integrer ?\nEntrez le chiffre ou la lettre correspondant(e) : ");
                    scanf("%s", grp);
                    grp[0] = toupper(grp[0]);
                }
                while (strlen(grp) != 1 || isalnum(grp[0]) == 0);

                //Updating the reader
                reader[index + strlen("Type : Groupe ")] = grp[0];

                //Updating the file
                fwrite(reader , sizeof(char) , strlen(reader) , modi);

                printf("\nFichier modifie avec succes !");

            }
        }
    }

    if (strcmp(rep , "se") == 0)
    {
        free(rep);

        printf("Modifier seance effectuees :\n");
        printf("\nChoissez entre :\n'a' pour ajouter\n'm' pour modifier\n's' pour supprimer");
        printf("\nReponse : ");

        char* rep = malloc(2);
        scanf("%s", rep);

        if (strcmp(rep , "a") == 0)
        {
            addseance("Seances effectuees" , reader , modi , 1);
        }

        if (strcmp(rep , "m") == 0)
        {
            modseance(reader , modi , strfinder("Seances effectuees" , reader , 0 , strlen(reader)) , strfinder("Seances ratees" , reader , 0 , strlen(reader)) , 1);
        }

        if (strcmp(rep , "s") == 0)
        {
            delseance(reader , modi , strfinder("Seances effectuees" , reader , 0 , strlen(reader)) , strfinder("Seances ratees" , reader , 0 , strlen(reader)) , 1);
        }

        free(rep);
    }

    if (strcmp(rep , "sr") == 0)
    {
        free(rep);

        printf("Modifier seance ratees :\n");
        printf("\nChoissez entre :\n'a' pour ajouter\n'm' pour modifier\n's' pour supprimer");
        printf("\nReponse : ");

        char* rep = malloc(2);
        scanf("%s", rep);
        rep[0] = toupper(rep[0]);
        rep[1] ='\0';

        if (strcmp(rep , "A") == 0)
        {
            addseance("Seances ratees" , reader , modi , 1);
        }

        if (strcmp(rep , "M") == 0)
        {
            modseance(reader , modi , strfinder("Seances ratees" , reader , 0 , strlen(reader)) ,strfinder("Paiement" , reader , 0 , strlen(reader)) , 1);
        }

        if (strcmp(rep , "S") == 0)
        {
            delseance(reader , modi , strfinder("Seances ratees" , reader , 0 , strlen(reader)) ,strfinder("Paiement" , reader , 0 , strlen(reader)) , 1);
        }

        free(rep);
    }

    if (strcmp(rep , "p") == 0)
    {
        free(rep);

        //Les dates de paiement
        printf("Modifier Paiement :\n");
        printf("\nChoissez entre :\n'a' pour ajouter\n'm' pour modifier\n's' pour supprimer");
        printf("\nReponse : ");

        char* rep = malloc(2);
        scanf("%s", rep);
        rep[0] = toupper(rep[0]);
        rep[1] ='\0';

        if (strcmp(rep , "A") == 0)
        {
            addseance("Paiement" , reader , modi , -1);
        }

        if (strcmp(rep , "M") == 0)
        {
            modseance(reader , modi , strfinder("Paiement" , reader , 0 , strlen(reader)) , strlen(reader) , -1);
        }

        if (strcmp(rep , "S") == 0)
        {
            delseance(reader , modi , strfinder("Paiement" , reader , 0 , strlen(reader)) , strlen(reader) , -1);
        }

        free(rep);
    }
}

int strfinder(char* found , char* list , int start , int stop)
{
    int len1 = strlen(found);

    for (int i = start ; i < stop - len1 ; i++)
    {
        char read[len1 + 1];

        for (int j = 0 ; j < len1 ; j++)
        {
            read[j] = list[i + j];
        }
        read[len1] = 0;

        if (strcmp(read , found) == 0)
        {
            return i;
        }
    }

    return -1;
}

void makeplace(int index , int places , char* reader)
{
    for (int i = strlen(reader) ; i > index - 1 ; i--)
    {
        reader[i + places] = reader[i];
    }

    for (int i = 0 ; i < places ; i++)
    {
        reader[index + i] = ' ';
    }

}

int confirmation(void)
{
    char* rep = malloc(4);
    printf("\nRepondez par 'oui' ou 'non' : ");
    scanf("%s", rep);

    for (int i = 0 ; i < 3 ; i++)
    {
        rep[i] = toupper(rep[i]);
    }

    if (strcmp(rep , "NON") == 0)
    {
        free(rep);
        return 0;
    }

    else if (strcmp(rep , "OUI") == 0)
    {
        free(rep);
        return 1;
    }
    
    else
    {
        free(rep);
        return -1;
    }
}

void delplace(int index , int space , char* reader)
{
    for (int i = index ; i < strlen(reader) + 1 - space ; i++)
    {
        reader[i] = reader[i + space];
    }
}

void addseance(char* seance , char* reader , FILE* modi , int seance_paie)
{
    //Size
    int index = strfinder(seance , reader , 0 , strlen(reader));
    int length = strlen(seance);
    if (strcmp(seance , "Paiement") == 0)
    {
        length = strlen("Paiement : +00h");
    }

    //Getting input
    char* se = malloc(30);
    int check = 1;
    do
    {
        if (check == 0)
        {
            printf("Le format doit etre de type jj/mm/aaaa !\n");
        }
        printf("\nDate (format jj/mm/aaaa) : ");
        scanf("%s", &se[0]);
        check = checkdate(se);
    }
    while (check == 0);

    se[10] = ' ';
    se[11] = ':';
    se[12] = ' ';

    do
    {
        if (check == 0)
        {
            printf("Le nombre d'heure doit etre un chiffre compris entre 0 et 9 !\n");
        }
        printf("Nombre d'heures : ");
        scanf("%s", &se[13]);
        check = checkhour(&se[13]);
    }
    while (check == 0);

    se[15] = 'h';
    se[16] = 10;
    se[17] = '\0';

    //Updating buffer
    int indexadd = index + length + 1;
    makeplace(indexadd , strlen(se) , reader);

    for (int i = 0 ; i < strlen(se) ; i++)
    {
        reader[indexadd + i] = se[i];
    }

    //Updating the file
    fwrite(reader , sizeof(char) , strlen(reader) , modi);

    //Updating paiement
    int add = atoi(&se[13]);
    add = add * (-1) * seance_paie;
    updatepaie(reader , add , modi);

    //End
    free(se);
    printf("\nFichier modifie avec succes !\n");

}

void convert(int num , char* numstring)
{
    if (num < 10 && num > -10)
    {
        if (num < 0)
        {
            numstring[0] = '-';
            numstring[1] = '0';
            numstring[2] = (num * (-1)) + 48;
        }
        else
        {
            numstring[0] = '+';
            numstring[1] = '0';
            numstring[2] = num + 48;
        }
        
    }

    if (num > 9)
    {
        numstring[0] = '+';
        numstring[1] = ((num - (num % 10)) / 10) + 48;
        numstring[2] = (num % 10) + 48;
    }

    if (num < -9)
    {
        num = num * (-1);
        numstring[0] = '-';
        numstring[1] = ((num - (num % 10)) / 10) + 48;
        numstring[2] = (num % 10) + 48;
    }

    numstring[3] = '\0';
}

void delseance(char* reader , FILE* modi , int start , int end , int seance_paie)
{
    printf("\nSuppression :\n");

    //Getting input
    char* se = malloc(19);
    int check = 1;
    do
    {
        if (check == 0)
        {
            printf("Le format doit etre de type jj/mm/aaaa !\n");
        }
        printf("\nDate (format jj/mm/aaaa) : ");
        scanf("%s", &se[0]);
        check = checkdate(se);
    }
    while (check == 0);

    se[10] = ' ';
    se[11] = ':';
    se[12] = ' ';

    do
    {
        if (check == 0)
        {
            printf("Le nombre d'heure doit etre un chiffre compris entre 0 et 9 !\n");
        }
        printf("Nombre d'heures : ");
        scanf("%s", &se[13]);
        check = checkhour(&se[13]);
    }
    while (check == 0);

    se[15] = 'h';
    se[16] = 10;
    se[17] = '\0';

    //Searching for it
    int index = strfinder(se , reader , start , end);

    if (index == -1)
    {
        printf("Seance introuvable ! Veuillez reesayez\n");
        free(se);
        return;
    }

    //Deleting it
    delplace(index , strlen(se) , reader);
    
    //Updating the file
    fwrite(reader , sizeof(char) , strlen(reader) , modi);

    //Updating paiement
    int add = atoi(&se[13]);
    add = add * seance_paie;
    updatepaie(reader , add , modi);

    //End
    free(se);
    printf("\nFichier modifie avec succes !\n");
}

void modseance(char* reader , FILE* modi , int start , int end , int seance_paie)
{
    printf("\nModification de seance :\n");

    //Getting input
    char* se = malloc(19);
    int check = 1;
    do
    {
        if (check == 0)
        {
            printf("Le format doit etre de type jj/mm/aaaa !\n");
        }
        printf("\nDate (format jj/mm/aaaa) : ");
        scanf("%s", &se[0]);
        check = checkdate(se);
    }
    while (check == 0);

    se[10] = ' ';
    se[11] = ':';
    se[12] = ' ';

    do
    {
        if (check == 0)
        {
            printf("Le nombre d'heure doit etre un chiffre compris entre 0 et 9 !\n");
        }
        printf("Nombre d'heures : ");
        scanf("%s", &se[13]);
        check = checkhour(&se[13]);
    }
    while (check == 0);

    se[15] = 'h';
    se[16] = 10;
    se[17] = '\0';

    //Searching for it
    int index = strfinder(se , reader , start , end);

    if (index == -1)
    {
        printf("Seance introuvable ! Veuillez reesayez");
    }

    //Getting past hours
    int add1 = atoi(&se[13]);
    add1 = add1 * seance_paie;

    //Modify
    printf("\nQue voulez vous modifier ?\nChoisissez entre : ");
    printf("\n'd' pour Date\n'h' pour Nombre d'heures\n");
    printf("Reponse : ");
    char* reponse = malloc(10);
    scanf("%s", reponse);
    reponse[0] = toupper(reponse[0]);
    reponse[1] = '\0';

    if (strcmp(reponse , "D") == 0)
    {
        char* date = malloc(20);
        int check = 1;
        do
        {
            if (check == 0)
            {
                printf("Le format doit etre de type jj/mm/aaaa !\n");
            }
            printf("Veulliez entrer la nouvelle date (format jj/mm/aaaa) : ");
            scanf("%s", date);
            check = checkdate(date);
        }
        while (check == 0);

        for (int i = 0 ; i < strlen(date) ; i++)
        {
            se[i] = date[i];
        }
        free(date);
    }

    else if (strcmp(reponse , "H") == 0)
    {
        char* hours = malloc(10);
        do
        {
            if (check == 0)
            {
                printf("Le nombre d'heure doit etre un chiffre compris entre 0 et 9 !\n");
            }
            printf("Nombre d'heures : ");
            scanf("%s", hours);
            check = checkhour(hours);
        }
        while (check == 0);

        se[13] = hours[0];
        se[14] = hours[1];

        free(hours);
    }

    free(reponse);

    //Updating buffer
    for (int i = 0 ; i < strlen(se) ; i++)
    {
        reader[index + i] = se[i];
    }

    //Updating the file
    fwrite(reader , sizeof(char) , strlen(reader) , modi);

    //Updating paiement
    int add2 = atoi(&se[13]);
    add2 = add2 * (-1) * seance_paie;
    updatepaie(reader , add1 + add2 , modi);

    //End
    free(se);
    printf("\nFichier modifie avec succes !\n");

}

int checkdate(char* date)
{
    //Length
    if (strlen(date) != 10)
    {
        return 0;
    }

    //Digits
    int check;
    for (int i = 0 ; i < 10 ; i++)
    {
        if (i == 2 || i == 5)
        {
            i++;
        }
        check = isdigit(date[i]);

        if (check == 0)
        {
            return 0;
        }
    }

    //Slash
    if (date[2] != '/' || date[5] != '/')
    {
        return 0;
    }

    //Confirm
    return 1;
}

int checkhour(char* hours)
{
    //Length
    if (strlen(hours) != 1 && strlen(hours) != 2)
    {
        return 0;
    }

    //Digit
    if (strlen(hours) == 1 && isdigit(hours[0]) == 0)
    {
        return 0;
    }

    if (strlen(hours) == 2 && (isdigit(hours[0]) == 0 || isdigit(hours[0]) == 0))
    {
        return 0;
    }

    //Confirm
    if (strlen(hours) == 1)
    {
        char digit = hours[0];
        hours[0] = '0';
        hours[1] = digit;
        hours[2] = '\0';
    }
    
    return 1;
}

void askeleve(char* eleve , char* name)
{
    //Asking for input
    do
    {
        if (strlen(eleve) == 0 || eleve[0] == ' ')
        {
            printf("\n");
        }

        if (strlen(eleve) == 0)
        {
            printf("\nVeuillez ecrire le nom avant de contimuer !\n");
        }

        if (eleve[0] == ' ')
        {
            printf("Le nom ne peut pas commencer par un espace !");
        }

        //Scan eleve
        printf("\nEleve : ");
        fgets(eleve , 29 , stdin);
        eleve[strlen(eleve) - 1] = '\0';
    }
    while (strlen(eleve) == 0 || eleve[0] == ' ');

    for (int i = 0 ; i < strlen(eleve) ; i++)
    {
        eleve[i] = toupper(eleve[i]);
    }

    //Getting student's file name
    strcpy(name , "eleves/");
    strcpy(&name[strlen("eleves/")] , eleve);

    int len = strlen("eleves/") + strlen(eleve);

    name[len] = '.';
    name[len + 1] = 't';
    name[len + 2] = 'x';
    name[len + 3] = 't';
    name[len + 4] = '\0';

}

void addeleve(char* eleve , char* name , int number)
{

    //Adding to data base
    FILE* addname = fopen("data/eleves.txt" , "a");
    fwrite(eleve , sizeof(char) , strlen(eleve), addname);
    fputc(10 , addname);

    FILE* addnm = fopen("data/nombre.txt" , "w");
    number++;
    fwrite(&number , sizeof(int) , 1 , addnm);

    //Copying from new file
    FILE* newp = fopen("data/NEW.txt" , "r");
    char* new = malloc(1000);

    fseek(newp , 0 , SEEK_END);
    int endf = ftell(newp);
    fseek(newp , 0 , SEEK_SET);
        
    fread(new , 1 , 60 , newp);
    new[60] = '\0';

    //Getting index
    int index = strfinder("Type : " , new , 0 , strlen(new));

    //Asking for data
    char* type = malloc(5);
    strcpy(type , "I");
    do
    {
        if (strlen(type) != 1 || (type[0] != 'I' && type[0] != 'G'))
        {
            printf("\n");
        }
        if (strlen(type) != 1)
        {
            printf("La reponse doit contenir un seul caractere seulement !\n");
        }
        if (type[0] != 'I' && type[0] != 'G')
        {
            printf("Choisissez seulement entre 'i' ou 'g' !\n");
        }
                    
        printf("\nChoissisez le type :\n'i' pour Individuel\n'g' pour Groupe\n");
        printf("\nReponse : ");

        scanf("%s", type);
        type[0] = toupper(type[0]);

    }
    while(strlen(type) != 1 || (type[0] != 'I' && type[0] != 'G'));

    //Updating buffer
    if (strcmp(type , "I") == 0)
    {
        makeplace(index + strlen("Type : ") , strlen("Individuel") , new);
        char indi[11] = "Individuel";

        for (int i = 0 ; i < strlen(indi) ; i++)
        {
            new[index + strlen("Type : ") + i] = indi[i];
        }
    }

     else if (strcmp(type , "G") == 0)
    {
        makeplace(index + strlen("Type : ") , strlen("Groupe X") , new);
        char grp[5];
        strcpy(grp , "A");

        do
        {
            if (strlen(grp) != 1 || isalnum(grp[0]) == 0)
            {
                printf("\n");
            }
            if(strlen(grp) != 1)
            {
                printf("La reponse ne doit contenir qu'un caractere !\n");
            }
            if (isalnum(grp[0]) == 0)
            {
                printf("Choisissez entre un chiffre ou une lettre seulement !\n");
            }

            printf("\nA quel groupe appartient t-il ?\nEntrez le chiffre ou la lettre correspondant(e) : ");
            scanf("%s", grp);
            grp[0] = toupper(grp[0]);
        }
        while (strlen(grp) != 1 || isalnum(grp[0]) == 0);

        strcpy(&new[index + strlen("Type : ")] , "Groupe ");
        new[index + strlen("Type : Groupe ")] = grp[0];
    }

    //Creating student's file
    FILE* stud = fopen(name , "w");
    fwrite(new , 1 , 60 + (strlen("Individuel")) , stud);
    fputc(10 , stud);
    fputc(10 , stud);

    printf("\n%s a ete inscrit !\n", eleve);
            
    fclose(addname);
    fclose(addnm);
    fclose(newp);
    fclose(stud);
    free(new);
    free(type);
}

void updatepaie(char* reader , int add , FILE* modi)
{
    fseek(modi , 0 , SEEK_SET);
    //Getting the actual paiement
    int index = strfinder("Paiement : " , reader , 0 , strlen(reader));

    char* numstring = malloc(4);

    for (int i = 0 ; i < 3 ; i++)
    {
        numstring[i] = reader[index + strlen("Paiement : ") + i];
    }
    numstring[3] = '\0';
        
    int num = atoi(numstring);

    //Doing operation on it
    num = num + add;

    //Updating buffer
    convert(num , numstring);
    for (int i = 0 ; i < 3 ; i++)
    {
        reader[index + strlen("Paiement : ") + i] = numstring[i] ;
    }

    //Updating file
    fwrite(reader , sizeof(char) , strlen(reader) , modi);

    printf("\nPaiement modifie avec succes !");

    //End
    free(numstring);
}