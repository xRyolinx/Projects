#include <stdio.h>
#include <cs50.h>

//Functions declarations
int numdiv(int x);
void div(int x , int array[]);
int MAX(int x , int y[]);
int pgcd(int a , int b , int x[] , int y[]);

//Start
int main(void)
{
    //Getting how many numbers
    int numofnumb = get_int("How many numbers do you want to know theirs dividers ? ");
    printf("\n");

    int number[numofnumb];
    int numofdiv[numofnumb];

    //For each number
    for (int i = 0 ; i < numofnumb ; i++)
    {
        //Getting number
        number[i] = get_int("Number (%i) = ", i + 1);

        //Getting the number of dividers
        numofdiv[i] = numdiv(number[i]);

    }

    printf("\n");

    //Max of number of divisers to set the cases necessary for all of them
    int max = MAX(numofnumb , numofdiv);

    //Divider numeroted for each number
    int divider[numofnumb][numofdiv[max]];

    for (int i = 0 ; i < numofnumb ; i++)
    {
        printf("Number %i : number of dividers = %i\n", number[i] , numofdiv[i]);

        //Getting the dividers
        div(number[i] , divider[i]);

        for (int j = 0 ; j < numofdiv[i] ; j++)
        {
            printf("Number %i : divider number %i is %i\n", number[i] , j + 1 , divider[i][j]);
        }
        printf("\n");
    }

    //PGCD
    for (int i = 0 ; i < numofnumb ; i++)
    {
        for (int j = 0 ; j < numofnumb ; j++)
        {
            if (i == j)
            {
                break;
            }
            else
            {
                int PGCD = pgcd(numofdiv[i] , numofdiv[j] , divider[i] , divider[j]);
                printf("PGCD (%i , %i) = %i\n", number[i] , number[j] , PGCD);
            }
        }
    }

    printf("\n");
}



//Functions definitions
//Number of dividers
int numdiv(int x)
{
    int n = 0;

    for(int i = 1 ; i <= x ; i++)
    {
        float vq = x / (i * 1.0);
        int fq = x / i;
        if (vq - fq == 0)
        {
            n++;
        }
    }

    return n;
}

//Dividers
void div(int x , int array[])
{

    int n = 0;

    for(int i = 1 ; i <= x ; i++)
    {
        float vq = x / (i * 1.0);
        int fq = x / i;
        if (vq - fq == 0)
        {
            array[n] = i;
            n++;
        }
    }
}



//Max
int MAX(int x , int y[])
{
    int total;
    int i;

    //For each number
    for (i = 0 ; i < x ; i++)
    {
        int add;
        total = 0;

        //With every other number
        for (int j = 0 ; j < x ; j++)
        {
            if (y[i] < y[j])
            {
                add = 1;
            }
            else
            {
                add = 0;
            }

            total = total + add;
        }

        if (total == 0)
        {
            return i;
        }
    }

    if (total != 0)
    {
        return 0;
    }
    else
    {
        return i;
    }
}



//PGCD
int pgcd(int a , int b ,int x[] , int y[])
{
    //For number 1
        //Each of his dividers
        for (int i = a - 1 ; i >= 0 ; i--)
        {
            //With each divider of number 2
            for (int j = b - 1 ; j >= 0 ; j--)
            {
                if (x[i] == y[j])
                {
                    return x[i];
                }
            }
        }

    return 1;
}
