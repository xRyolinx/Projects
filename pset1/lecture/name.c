#include <stdio.h>
#include <cs50.h>
int main(void)
{
    string answer = get_string("what's your name ? \n");
    printf("Hi , %s\n", answer);
    return 0;
}