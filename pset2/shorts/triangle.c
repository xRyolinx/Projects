#include <stdio.h>
#include <cs50.h>

//Variables
float length[3];

//Functions' declarations
bool checking(void);

//Start
int main(void)
{
    //Getting the lenght of each side
    for (int i = 0 ; i < 3 ; i++)
    {
3            length[i] = get_float("Lenght %i : ", i + 1);

            //Checking the sign of the lenght
            if (length[i] < 0)
            {
                printf("The lenght must be positive !\n");
                return 1;
            }
    }

    //Check
    bool check = checking();

    //Result
    if (check == true)
    {
         printf("This can be a triangle !\n");
    }
    else
    {
         printf("This can't be a triangle !\n");
    }

    //Run programme
    return 0;
}


//Functions' definitions
bool checking(void)
{
    //Variables
    float total[3];

    //For each side
    for (int i = 0 ; i < 3 ; i++)
    {
        total[i] = - length[i];

        //Total of the other sides
        for (int n = 0 ; n < 3 ; n++)
        {
            total[i] = total[i] + length[n];
        }

        //Checking if the total isn't greater than the length
        if (total[i] <= length[i])
        {
            return false;
        }
    }

    return true;
}