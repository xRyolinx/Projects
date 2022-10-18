#include <stdio.h>
#include <string.h>
#include <cs50.h>

int player;
int x;
int y;

//Choosing (x,y)
string choose(int i ,int j)
{
    int check1;
    int check2;

    if(i == y && j == x)
    {
        if(player % 2 == 0)
        {
            return " X ";
        }
        else
        {
            return " O ";
        }
    }
    else
    {
        return "   ";
    }
    check1 = strcmp(choose(i , j) , "X ");
    check2 = strcmp(choose(i , j) , "O ");
    if(check1 != 0 || check2 != 0)
    {
    return "  ";
    }
}


//Display the game
void display(void)
{
    printf("%s%s%s%s%s\n", choose(3,1) , "|" , choose(3,2) , "|" , choose(3,3) );
    printf("---|---|---\n");
    printf("%s%s%s%s%s\n", choose(2,1) , "|" , choose(2,2) , "|" , choose(2,3) );
    printf("---|---|---\n");
    printf("%s%s%s%s%s\n", choose(1,1) , "|" , choose(1,2) , "|" , choose(1,3) );
    printf("\n");
}


int main(void)
{
    for(player = 0 ; player < 2 ; player++)
    {
        //Confirming x and y
        printf("Player %d\n", (player%2)+1);
        do
        {
            x = get_int("x = ");
            y = get_int("y = ");
        }
        while(x < 1 || x >3 || y < 1 || y >3);

            display();
    }
}
