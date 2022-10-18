#include <stdio.h>
#include <cs50.h>
#include <string.h>

typedef struct
{
    string name;
    string number;
}
person;

int main(void)
{
    person people[2];

    people[0].name = "Carter";
    people[0].number = "0557 93 29 69";

    people[1].name = "David";
    people[1].number = "0561 35 60 20";

    for (int i = 0 ; i < 2 ; i++)
    {
        if (strcmp(people[i].name , "David") == 0)
        {
            printf("Found : %s\n", people[i].number);
            return 0;
        }
    }

    printf("Not found\n");
    return 1;
}