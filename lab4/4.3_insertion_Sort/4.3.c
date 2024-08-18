#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000
#define MAXSTEPS 20

void write_arrays_to_csv(int steps[], double time[], int size)
{
    FILE *file = fopen("data.csv", "w");

    // Column headers
    fprintf(file, "Input Size,Time Taken\n");

    // Array data
    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%d, %lf\n", steps[i], time[i]);
    }

    fclose(file);
}

void insertion_sort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main()
{
    FILE *fptr = fopen("randRange.txt", "r");
    if (!fptr)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int inputs[MAX];
    for (int i = 0; i < MAX; i++)
    {
        if (fscanf(fptr, "%d", &inputs[i]) != 1)
        {
            fprintf(stderr, "Error reading number from file\n");
            fclose(fptr);
            exit(EXIT_FAILURE);
        }
    }
    fclose(fptr);

    int step_size;
    printf("Enter number of steps: ");
    scanf("%d", &step_size);

    int steps[step_size];

    printf("Enter inputs for each step: ");
    for (int i = 0; i < step_size; i++)
    {
        scanf("%d", &steps[i]);
    }

    double time[step_size];

    for (int k = 0; k < step_size; k++)
    {
        int n = steps[k];
        clock_t start = clock();

        insertion_sort(inputs, n);

        clock_t end = clock();
        double time_elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
        time[k] = time_elapsed;

        printf("Time taken to sort %d elements: %f seconds\n", n, time_elapsed);
    }

    write_arrays_to_csv(steps, time, 5);

    return 0;
}