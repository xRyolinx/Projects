#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

//Declaring functions
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

//Start
int main(void)
{
    //Insert the text
    string text = get_string("Text : ");

    //Variables
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    //Averages
    float L = (letters / (words * 1.0)) * 100;
    float S = (sentences / (words * 1.0)) * 100;

    //Index
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index > 16)
    {
        printf("Grade 16+\n");
    }

    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }

    else
    {
        printf("Grade %i\n", index);
    }

    return 0;
}


//Define functions

//Letters
int count_letters(string text)
{
    //Variables
    int letters = 0;
    int add = 0;

    //Number of letters
    for (int i = 0 ; i < strlen(text) ; i++)
    {
        if (islower(text[i]) != 0 || isupper(text[i]) != 0)
        {
            add = 1;
        }

        else
        {
            add = 0;
        }

        //Total
        letters = letters + add;
    }

    return letters;
}


//Words
int count_words(string text)
{
    //Variables
    int words = 1;
    int add = 0;

    //Number of words
    for (int i = 0 ; i < strlen(text) ; i++)
    {
        if (text[i] == ' ')
        {
            add = 1;
        }

        else
        {
            add = 0;
        }

        //Total
        words = words + add;
    }

    return words;
}



//Sentences
int count_sentences(string text)
{
    //Variables
    int sentences = 0;
    int add = 0;

    //Number of sentences
    for (int i = 0 ; i < strlen(text) ; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            add = 1;
        }

        else
        {
            add = 0;
        }

        //Total
        sentences = sentences + add;
    }

    return sentences;
}