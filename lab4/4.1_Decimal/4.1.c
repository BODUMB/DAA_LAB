#include <stdio.h>
#include <stdlib.h>

void decimalToBinary(int decimal, FILE *output)
{
    if (decimal > 1)
    {
        decimalToBinary(decimal / 2, output);
    }
    fprintf(output, "%d", decimal % 2);
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: <n> <in_> <output_file>\n");
        return 1;
    }

    int n = atoi(argv[1]);
    char *inFile = argv[2];
    char *outFile = argv[3];

    FILE *inPtr = fopen(inFile, "r");
    FILE *outPtr = fopen(outFile, "w");

    if (inPtr == NULL)
        return 1;

    int decimal;
    int i = 0;

    while (i < n && fscanf(inPtr, "%d", &decimal) == 1)
    {
        fprintf(outPtr, "The binary equivalent of %d is ", decimal);
        decimalToBinary(decimal, outPtr);
        fprintf(outPtr, "\n");

        i++;
    }

    fclose(inPtr);
    fclose(outPtr);

    return 0;
}