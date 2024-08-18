#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int main()
{
    int N;
    printf("Enter how many numbers you want to read from file: ");
    scanf("%d", &N);

    int a[N];

    FILE *fptr = fopen("q3.txt", "r");

    int max = INT_MIN;
    for (int i = 0; i < N; i++)
    {
        if (fscanf(fptr, "%d", &a[i]) != 1)
        {
            printf("Error reading file.\n");
            fclose(fptr);
            return 1;
        }
        if (a[i] > max)
            max = a[i];
    }
    fclose(fptr);

    printf("Content of the array:\n");
    for (int i = 0; i < N; i++)
        printf("%d ", a[i]);
    printf("\n");

    int freq[max + 1];
    memset(freq, 0, (max + 1) * sizeof(int));

    for (int i = 0; i < N; i++)
        freq[a[i]]++;

    int duplicate_count = 0;
    int max_freq = 0;
    int most_repeating = 0;

    for (int i = 0; i < max + 1; i++)
    {
        if (freq[i] > 1)
            duplicate_count++;
        if (freq[i] > max_freq)
        {
            max_freq = freq[i];
            most_repeating = i;
        }
    }

    printf("a) Total number of duplicate elements: %d\n", duplicate_count);
    printf("b) Most repeating element: %d\n", most_repeating);

    printf("\n");
    return 0;
}