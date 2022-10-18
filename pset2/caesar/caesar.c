#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//Variables
int key;

//Declaring functions
string rotate(string text);
int convert(string entered);
int check(string entered);

//Start
int main(int argc, string argv[])
{
    //Checking the key
    if (argc != 2 || check(argv[1]) != 0)
    {
        return 1;
    }

    //Insert plaintext
    string plaintext = get_string("plaintext: ");

    //Getting the key in int
    key = convert(argv[1]);

    //Cipher the text
    string ciphertext = rotate(plaintext);
    printf("ciphertext: %s\n", ciphertext);
}


//Define functions

//Getting the key
int convert(string entered)
{
    //Variables
    int lenkey = strlen(entered);
    int num[lenkey];
    int total = 0;
    long long int value;

    //Converting the key into int
    for (int i = 0 ; i < lenkey ; i++)
    {
        //converting numbers of each rank
        if (isdigit(entered[i]) != 0)
        {
            num[i] = entered[i] - 48;
        }

        //Getting value of number of each rank
        value = num[i] * pow(10, lenkey - (i + 1));

        //Value of key
        total = total + value;
    }

    return total;
}


//Shift letters
string rotate(string text)
{
    for (int i = 0 ; i < strlen(text) ; i++)
    {
        //Shifting lower-case letters
        if (islower(text[i]) != 0)
        {
            text[i] = (((text[i] - 97) + key) % 26) + 97;
        }

        //Shifting upper-case letters
        if (isupper(text[i]) != 0)
        {
            text[i] = (((text[i] - 65) + key) % 26) + 65;
        }
    }

    return text;
}


//Check key
int check(string entered)
{
    //Variables
    int add;
    int total = 0;

    //checking
    for (int i = 0 ; i < strlen(entered) ; i++)
    {
        //if non-numeric
        if (entered[i] < 48 || entered[i] > 57)
        {
            add = 1;
        }

        //if numeric
        else
        {
            add = 0;
        }

        //Total
        total = total + add;
    }

    return total;
}