#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Variables
string key;

//Declaring functions
int checkal(string entered);
int checkrep(string entered);
string shift(string text);


//Start
int main(int argc, string argv[])
{
    //Cheking the key
    if (argc != 2 || strlen(argv[1]) != 26 || checkal(argv[1]) != 0 || checkrep(argv[1]) != 0)
    {
        if (argc != 2)
        {
            printf("Please enter 1 key only !\n");
            return 1;
        }

        if (strlen(argv[1]) != 26)
        {
            printf("Key must contain 26 characters !\n");
        }

        if (checkal(argv[1]) != 0)
        {
            printf("Key must coutain alphabetical characters only !\n");
        }

        if (checkrep(argv[1]) != 0)
        {
            printf("Key must not contain repetitions !\n");
        }

        return 1;
    }

    //Get the key
    key = argv[1];

    //Insert plaintext
    string plaintext = get_string("plaintext: ");

    //Cipher
    string ciphertext = shift(plaintext);
    printf("ciphertext: %s\n", ciphertext);
}

//Check key
//Check alphabetical
int checkal(string entered)
{
    //Variables
    int add;
    int total = 0;

    //checking
    for (int i = 0 ; i < strlen(entered) ; i++)
    {
        //Getting all the letters to upper-case
        entered[i] = toupper(entered[i]);

        //if non-alphabetic
        if (isalpha(entered[i]) == 0)
        {
            add = 1;
        }

        //if alphabetic
        else
        {
            add = 0;
        }

        //Total
        total = total + add;
    }

    return total;
}


//Check repetition
int checkrep(string entered)
{
    //Variables
    int add;
    int total = 0;

    //For each character
    for (int i = 0 ; i < strlen(entered) ; i++)
    {
        //Compare with every other characters
        for (int n = 0 ; n < strlen(entered) ; n++)
        {
            if (entered[i] == entered[n])
            {
                add = 1;
            }

            else
            {
                add = 0;
            }

            //Total
            total = total + add;
        }

        //Removing the first repetition
        total = total - 1;
    }

    return total;
}


//Shifting letters
string shift(string text)
{
    //Variables
    int len = strlen(text);
    int num[len];

    //Shifting
    for (int i = 0 ; i < len ; i++)
    {
        //Lower-case letters
        if (islower(text[i]) != 0)
        {
            num[i] = text[i] - 97;
            text[i] = tolower(key[num[i]]);
        }

        //Upper-case letters
        if (isupper(text[i]) != 0)
        {
            num[i] = text[i] - 65;
            text[i] = toupper(key[num[i]]);
        }
    }
    return text;
}