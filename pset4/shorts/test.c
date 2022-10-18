#include <stdio.h>
#include <string.h>

int main(void)
{
    char* phrase = "Hello world !";
    FILE* ptr = fopen("file.txt" , "w");

    fwrite(phrase , sizeof(char) , strlen(phrase) , ptr);

    return 0;
}