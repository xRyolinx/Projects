// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    //if (argc != 4)
    //{
      //  printf("Usage: ./volume input.wav output.wav factor\n");
        //return 1;
    //}

    argv[1] = "input.wav";
    argv[2] = "output.wav";
    argv[3] = "2.0";

    // Open files and determine scaling factor
    FILE* input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE* output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    uint8_t header[HEADER_SIZE];
    fread(header , sizeof(uint8_t) , HEADER_SIZE , input);
    fwrite(header , sizeof(uint8_t) , HEADER_SIZE , output);

    // TODO: Read samples from input file and write updated data to output file
    long int byte1 = ftell(input);
    long int byte2 = ftell(output);
    printf("Input : %li\nOutput : %li\n", byte1 , byte2);

    fseek(input , 0 , SEEK_END);
    long int byte3 = ftell(input);
    printf("End of Input : %li\n", byte3);

    fseek(input , 44 , SEEK_SET);
    long int byte4 = ftell(input);
    printf("Input : %li\n", byte4);


    int16_t buffer;
    int count = 44;
    while (count != byte3)
    {
        fread(&buffer , 2 , 1 , input);
        buffer = buffer * factor;
        fwrite(&buffer , 2 , 1 , output);
        count++;
    }


    // Close files
    fclose(input);
    fclose(output);
}
