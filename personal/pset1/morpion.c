//Libraries
#include <stdio.h>
#include <string.h>
#include "cs50.c"

//Variables
int player;

string rep;

string x1 = " ";
string x2 = " ";
string x3 = " ";
string x4 = " ";
string x5 = " ";
string x6 = " ";
string x7 = " ";
string x8 = " ";
string x9 = " ";

//Display
void display(void)
{
    printf("\n");
    printf("  %s%s%s%s%s\n", x7, " | ", x8, " | ", x9);
    printf(" ---|---|---\n");
    printf("  %s%s%s%s%s\n", x4, " | ", x5, " | ", x6);
    printf(" ---|---|---\n");
    printf("  %s%s%s%s%s\n", x1, " | ", x2, " | ", x3);
    printf("\n");
}

//Num player
float num(int n)
{
    return (n % 2) + 1 ;
}

//Game
int main(void)
{
    //Start
    printf(" TIC TAC TOE\n");
    display();

    //Players
    for (player = 0 ; player < 9 ; player++)
    {
        //rep players
        if (player % 2 == 0)
        {
            rep = "X";
        }
        else
        {
            rep = "O";
        }

        //reboot answer
        int answer = 12122001;

        //Choosing and confirming the case
        printf("Turn : Player %.0f\n", num(player));
        do
        {
            if ((answer > 9 || answer < 1) && answer != 12122001)
            {
                printf("The number must be between 1 and 9 !\n");
            }
            else if
              ((answer == 1 && (strcmp(x1, "X") == 0 || strcmp(x1, "O") == 0))
            || (answer == 2 && (strcmp(x2, "X") == 0 || strcmp(x2, "O") == 0))
            || (answer == 3 && (strcmp(x3, "X") == 0 || strcmp(x3, "O") == 0))
            || (answer == 4 && (strcmp(x4, "X") == 0 || strcmp(x4, "O") == 0))
            || (answer == 5 && (strcmp(x5, "X") == 0 || strcmp(x5, "O") == 0))
            || (answer == 6 && (strcmp(x6, "X") == 0 || strcmp(x6, "O") == 0))
            || (answer == 7 && (strcmp(x7, "X") == 0 || strcmp(x7, "O") == 0))
            || (answer == 8 && (strcmp(x8, "X") == 0 || strcmp(x8, "O") == 0))
            || (answer == 9 && (strcmp(x9, "X") == 0 || strcmp(x9, "O") == 0)))
            {
                printf("This case is already full !\n");
            }
            answer = get_int("Please choose the case : ");
        }
        while
          ((answer > 9 || answer < 1)
        || (answer == 1 && (strcmp(x1, "X") == 0 || strcmp(x1, "O") == 0))
        || (answer == 2 && (strcmp(x2, "X") == 0 || strcmp(x2, "O") == 0))
        || (answer == 3 && (strcmp(x3, "X") == 0 || strcmp(x3, "O") == 0))
        || (answer == 4 && (strcmp(x4, "X") == 0 || strcmp(x4, "O") == 0))
        || (answer == 5 && (strcmp(x5, "X") == 0 || strcmp(x5, "O") == 0))
        || (answer == 6 && (strcmp(x6, "X") == 0 || strcmp(x6, "O") == 0))
        || (answer == 7 && (strcmp(x7, "X") == 0 || strcmp(x7, "O") == 0))
        || (answer == 8 && (strcmp(x8, "X") == 0 || strcmp(x8, "O") == 0))
        || (answer == 9 && (strcmp(x9, "X") == 0 || strcmp(x9, "O") == 0)));

        //Changing Variables
        if (answer == 1)
        {
            x1 = rep;
        }
        else if (answer == 2)
        {
            x2 = rep;
        }
        else if (answer == 3)
        {
            x3 = rep;
        }
        else if (answer == 4)
        {
            x4 = rep;
        }
        else if (answer == 5)
        {
            x5 = rep;
        }
        else if (answer == 6)
        {
            x6 = rep;
        }
        else if (answer == 7)
        {
            x7 = rep;
        }
        else if (answer == 8)
        {
            x8 = rep;
        }
        else if (answer == 9)
        {
            x9 = rep;
        }

        //fill table
        display();

        //end game
        if((strcmp(x1, rep) == 0 && strcmp(x2, rep) == 0 && strcmp(x3, rep) == 0)
        || (strcmp(x4, rep) == 0 && strcmp(x5, rep) == 0 && strcmp(x6, rep) == 0)
        || (strcmp(x7, rep) == 0 && strcmp(x8, rep) == 0 && strcmp(x9, rep) == 0)
        || (strcmp(x1, rep) == 0 && strcmp(x4, rep) == 0 && strcmp(x7, rep) == 0)
        || (strcmp(x2, rep) == 0 && strcmp(x5, rep) == 0 && strcmp(x8, rep) == 0)
        || (strcmp(x3, rep) == 0 && strcmp(x6, rep) == 0 && strcmp(x9, rep) == 0)
        || (strcmp(x1, rep) == 0 && strcmp(x5, rep) == 0 && strcmp(x9, rep) == 0)
        || (strcmp(x3, rep) == 0 && strcmp(x5, rep) == 0 && strcmp(x7, rep) == 0))
        {
            break;
        }
    }

    //Results

    //Win
    if((strcmp(x1, rep) == 0 && strcmp(x2, rep) == 0 && strcmp(x3, rep) == 0)
    || (strcmp(x4, rep) == 0 && strcmp(x5, rep) == 0 && strcmp(x6, rep) == 0 )
    || (strcmp(x7, rep) == 0 && strcmp(x8, rep) == 0 && strcmp(x9, rep) == 0 )
    || (strcmp(x1, rep) == 0 && strcmp(x4, rep) == 0 && strcmp(x7, rep) == 0 )
    || (strcmp(x2, rep) == 0 && strcmp(x5, rep) == 0 && strcmp(x8, rep) == 0 )
    || (strcmp(x3, rep) == 0 && strcmp(x6, rep) == 0 && strcmp(x9, rep) == 0 )
    || (strcmp(x1, rep) == 0 && strcmp(x5, rep) == 0 && strcmp(x9, rep) == 0 )
    || (strcmp(x3, rep) == 0 && strcmp(x5, rep) == 0 && strcmp(x7, rep) == 0 ))
    {
        printf("Player %.0f%s\n", num(player), " wins !");
    }
    //Draw
    else
    {
        printf("It's a draw !\n");
    }

    printf("\n");
}