#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Functions declaration
int check(int number , char* input , char* students[]);
int search(char* eleve , char* students[] , int number);
void modify(char* reader , FILE* modi);
int strfinder(char* found , char* list);
void makeplace(int index , int places , char* reader);
void delplace(int index , int space , char* reader);
int confirmation(void);
void addseance(char* seance , char* reader , FILE* modi);
void convert(int num , char* numstring);
void delseance(char* reader , FILE* modi);
void modseance(char* reader , FILE* modi);
int checkdate(char* date);
int checkhour(char* hours);
int checkpaie(char* paie);

//Start
int main(void)
{
    while(1)
    {
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
            students[i] = malloc(11);
        }

        printf("Liste d'eleves :\n\n");
        for (int i = 0 ; i < number ; i++)
        {
            int j = -1;
            int z = 0;

            char* read = malloc(11);
            read[0] = 'r';

            while (read[z] != '\0' && read[j] != ' ')
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

            printf("\nEntrez 'e' pour entrer\nEntrez 'q' pour quitter\nReponse : ");
            scanf("%s", entry);
            entry[0] = toupper(entry[0]);
            entry[1] = '\0';
        }
        while (strcmp(entry , "E") != 0 && strcmp(entry , "Q") != 0);

        //Quit
        if (strcmp(entry , "Q") == 0)
        {
            free(entry);
            fclose(nb);
            fclose(std);

            for (int i = 0 ; i < number ; i++)
            {
                free(students[i]);
            }

            break;
        }
        free(entry);


        //Asking for input
        char* eleve = malloc(11);
        printf("\nEleve : ");
        scanf("%s", eleve);

        for (int i = 0 ; i < strlen(eleve) ; i++)
        {
            eleve[i] = toupper(eleve[i]);
        }

        //Getting student's file name
        char* name = malloc(25);
        strcpy(name , "eleves/");
        strcpy(&name[strlen("eleves/")] , eleve);

        int len = strlen("eleves/") + strlen(eleve);

        name[len] = '.';
        name[len + 1] = 't';
        name[len + 2] = 'x';
        name[len + 3] = 't';
        name[len + 4] = '\0';

        //Comparing input with database
        int result = check(number , eleve , students);
        int inscri = 2;
        int sinscri = 0;

        if (result == 0)
        {
            printf("L'eleve n'est pas inscrit ! Voulez vous l'ajouter ?\n");
            inscri = confirmation();

            if (inscri == 1)
            {
                sinscri = 1;
                //Adding to data base
                FILE* addname = fopen("data/eleves.txt" , "a");
                fwrite(eleve , sizeof(char) , strlen(eleve) + 1 , addname);

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
                int index = strfinder("Type : " , new);

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
                        printf("\nLa reponse doit contenir un seul caractere seulement !");
                    }
                    if (type[0] != 'I' && type[0] != 'G')
                    {
                        printf("\nChoisissez seulement entre 'i' ou 'g' !");
                    }
                    
                    printf("\n\nChoissisez le type :\n'i' pour Individuel\n'g' pour Groupe\n");
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

                printf("\n%s a ete inscrit !\n", eleve);
            
                fclose(addname);
                fclose(addnm);
                fclose(newp);
                fclose(stud);
                free(new);
            }
            else
            {
                printf("\n%s n'a pas ete inscrit !\n", eleve);
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
                fwrite(students[i] , sizeof(char) , strlen(students[i]) + 1 , addname);
            }
            fclose(addname);

            printf("\n%s a ete retire avec succes !\n", eleve);

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
            printf("\n\n%s\n\n", reader);
        
            fclose(elefile);

            if (modif == 0)
            {
                free(reader);
            }

            if (modif == 1)
            {
                FILE* modi = fopen(name , "w");
                modify(reader , modi);
                fclose(modi);
                free(reader);
            }
        }

        //End programme
        printf("\nEntrez un caractere pour terminer : ");
        char* fini = malloc(10);
        scanf("%s", fini);
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
        int index = strfinder("Type : " , reader);
        int check1 = strfinder("Individuel" , reader);
        int check2 = strfinder("Groupe" , reader);

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
            addseance("Seances effectuees" , reader , modi);
        }

        if (strcmp(rep , "m") == 0)
        {
            modseance(reader , modi);
        }

        if (strcmp(rep , "s") == 0)
        {
            delseance(reader , modi);
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

        if (strcmp(rep , "a") == 0)
        {
            addseance("Seances ratees" , reader , modi);
        }

        if (strcmp(rep , "m") == 0)
        {
            modseance(reader , modi);
        }

        if (strcmp(rep , "s") == 0)
        {
            delseance(reader , modi);
        }

        free(rep);
}

    if (strcmp(rep , "p") == 0)
    {
        free(rep);

        //Getting the actual paiement
        printf("Modifier paiement");
        int index = strfinder("Paiement : " , reader);

        char* numstring = malloc(4);

        for (int i = 0 ; i < 3 ; i++)
        {
            numstring[i] = reader[index + strlen("Paiement : ") + i];
        }
        numstring[3] = '\0';
        
        int num = atoi(numstring);

        //Doing operation on it
        printf("\nEntrez le nombre que vous voulez additionnez ou soustraire : ");
        int add = 0;
        scanf("%i", &add);

        num = num + add;

        //Updating buffer
        convert(num , numstring);
        for (int i = 0 ; i < 3 ; i++)
        {
            reader[index + strlen("Paiement : ") + i] = numstring[i] ;
        }

        //Updating file
        fwrite(reader , sizeof(char) , strlen(reader) , modi);

        printf("\nFichier modifie avec succes !");

        //End
        free(numstring);
    }
}

int strfinder(char* found , char* list)
{
    int len1 = strlen(found);
    int len2 = strlen(list);

    for (int i = 0 ; i < len2 - len1 ; i++)
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

void addseance(char* seance , char* reader , FILE* modi)
{
    //Size
    int index = strfinder(seance , reader);

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


    se[14] = 'h';
    se[15] = ' ';

    do
    {
        if (check == 0)
        {
            printf("Repondez seulement par 'p' ou 'n' !\n");
        }
        printf("Chosissez 'p' si payee ou 'n' si non payee : ");
        scanf("%s", &se[16]);
        check = checkpaie(&se[16]);
    }
    while (check == 0);

    se[17] = 10;
    se[18] = '\0';

    //Updating buffer
    int indexadd = index + strlen(seance) + 1;
    makeplace(indexadd , strlen(se) , reader);

    for (int i = 0 ; i < strlen(se) ; i++)
    {
        reader[indexadd + i] = se[i];
    }
    free(se);

    //Updating the file
    fwrite(reader , sizeof(char) , strlen(reader) , modi);

    printf("\nFichier modifie avec succes !");
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

void delseance(char* reader , FILE* modi)
{
    printf("\nSuppression de seance :\n");

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

    se[14] = 'h';
    se[15] = ' ';

    do
    {
        if (check == 0)
        {
            printf("Repondez seulement par 'p' ou 'n' !\n");
        }
        printf("Chosissez 'p' si payee ou 'n' si non payee : ");
        scanf("%s", &se[16]);
        check = checkpaie(&se[16]);
    }
    while (check == 0);

    se[17] = 10;
    se[18] = '\0';

    //Searching for it
    int index = strfinder(se , reader);

    if (index == -1)
    {
        printf("Seance introuvable ! Veuillez reesayez");
    }

    //Deleting it
    delplace(index , strlen(se) , reader);
    free(se);

    //Updating the file
    fwrite(reader , sizeof(char) , strlen(reader) , modi);

    printf("\nFichier modifie avec succes !");
}

void modseance(char* reader , FILE* modi)
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

    se[14] = 'h';
    se[15] = ' ';

    do
    {
        if (check == 0)
        {
            printf("Repondez seulement par 'p' ou 'n' !\n");
        }
        printf("Chosissez 'p' si payee ou 'n' si non payee : ");
        scanf("%s", &se[16]);
        check = checkpaie(&se[16]);
    }
    while (check == 0);

    se[17] = 10;
    se[18] = '\0';

    //Searching for it
    int index = strfinder(se , reader);

    if (index == -1)
    {
        printf("Seance introuvable ! Veuillez reesayez");
    }

    //Modify
    printf("\nQue voulez vous modifier ?\nChoisissez entre : ");
    printf("\n'd' pour Date\n'h' pour Nombre d'heures\n'p' pour Paiement\n");
    printf("Reponse : ");
    char* reponse = malloc(2);
    scanf("%s", reponse);

    if (strcmp(reponse , "d") == 0)
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

    else if (strcmp(reponse , "h") == 0)
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

        free(hours);
    }

    else if (strcmp(reponse , "p") == 0)
    {
        char* paie = malloc(10);
        do
        {
            if (check == 0)
            {
                printf("Repondez seulement par 'p' ou 'n' !\n");
            }
            printf("Chosissez 'p' si payee ou 'n' si non payee : ");
            scanf("%s", paie);
            check = checkpaie(paie);
        }
        while (check == 0);

        se[16] = paie[0];

        free(paie);
    }
    free(reponse);

    //Updating buffer
    for (int i = 0 ; i < strlen(se) ; i++)
    {
        reader[index + i] = se[i];
    }
    free(se);

    //Updating the file
    fwrite(reader , sizeof(char) , strlen(reader) , modi);
    printf("\nFichier modifie avec succes !");
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
    if (strlen(hours) != 1)
    {
        return 0;
    }

    //Digit
    if (isdigit(hours[0]) == 0)
    {
        return 0;
    }

    //Confirm
    return 1;
}

int checkpaie(char* paie)
{
    //Length
    if (strlen(paie) != 1)
    {
        return 0;
    }

    //n or p
    if (paie[0] != 'p' && paie[0] != 'n')
    {
        return 0;
    }

    //Confirm
    return 1;
}