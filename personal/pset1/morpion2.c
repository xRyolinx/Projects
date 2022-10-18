#include <stdio.h>
#include <math.h>
#include <string.h>
#include <cs50.h>

int player;
int x;
int y;
int a;
int b;
int z;
string rep;

//Choosing (x,y)
string choose(int i , int j)
{
    a = i;
    b = j;

    //rep player
    if(player % 2 == 0)
    {
        rep = " X ";
    }
    else
    {
         rep = " O ";
    }

    //fill table
    if((i == y && j == x) || (i == 0 && j == 0))
    {
        return rep;
    }
    else
    {
        rep = "   ";
        return rep;
    }

}


//Display the game
void display(void)
{
    printf("3  %s%s%s%s%s\n", choose(3,1) , "|" , choose(3,2) , "|" , choose(3,3) );
    printf("   ---|---|---\n");
    printf("2  %s%s%s%s%s\n", choose(2,1) , "|" , choose(2,2) , "|" , choose(2,3) );
    printf("   ---|---|---\n");
    printf("1  %s%s%s%s%s\n", choose(1,1) , "|" , choose(1,2) , "|" , choose(1,3));
    printf("\n");
    printf("    1   2   3\n");
    printf("\n");
}

//Game
int main(void)
{
    //Start
    printf("\n");
    x = 0;
    y = 0;

    printf("  TIC TAC TOE\n");
    printf("\n");
    display();

    //Mid game
    for(player = 0 ; player < 4 ; player++)
    {
        //Player
        printf("Player %d%s%s%s\n", (player%2)+1 , "  (" , rep , ")" );

        //Confirming and getting (x,y)
        do
        {
            x = get_int("x = ");
            y = get_int("y = ");
        }
        while(x < 1 || x >3 || y < 1 || y >3);

        display();

        //remembering variables
        int check1;
        int check2;
        int q = a;
        int p = b;
        check1 = strcmp(choose(q , p) , " X ");
        check2 = strcmp(choose(q , p) , " O ");
        if(check1 == 0 )
        {
        z = 1;
        }
        else
        {
        z = 0;
        }

        if(check2 == 0 )
        {
        z = 2;
        }
        else
        {
        z = 0;
        }

        //
        if (z == 0)
        {
            rep = "   ";
        }
        else if (z == 1)
        {
            rep = " X ";
        }
        else
        {
            rep = " O ";
        }
    }
}

