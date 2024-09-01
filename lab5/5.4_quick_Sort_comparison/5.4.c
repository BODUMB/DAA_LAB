#include <stdio.h>
#include <stdlib.h>
#define MAX 10000
#define MAXSTEPS 20

long long comparisons = 0;

// Function to perform insertion sort
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        // Move elements of arr[0..i-1] that are greater than key
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key)
        {
            ++comparisons;
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
        if (j >= 0)
            ++comparisons; // Count comparison for the last valid condition
    } 
}

// Print comparisons
double *compare_inputs(int inputs[], int steps[], int size)
{
    double *cmp_arr = (double *)malloc(size * sizeof(double));
    for (int k = 0; k < size; k++)
    {
        int n = steps[k];
        comparisons = 0;
        int *temp = (int *)malloc(n * sizeof(int)); // Sort copy of original input
        for (int i = 0; i < n; i++)
            temp[i] = inputs[i];
        insertionSort(temp, n);
        cmp_arr[k] = comparisons;
        printf("%d elements: %lld\n", n, comparisons);
        free(temp);
    }
    printf("\n");
    return cmp_arr;
}

void write_to_csv(int steps[], double avg_cmp[], double best_cmp[], int size)
{
    FILE *file = fopen("data.csv", "w");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    // Column headers
    fprintf(file, "Input Size,Avg Case Comparisons,Best Case Comparisons\n");
    // Array data
    for (int i = 0; i < size; i++)
        fprintf(file, "%d, %lf, %lf\n", steps[i], avg_cmp[i], best_cmp[i]);
    fclose(file);
}

int main()
{
    // Read unsorted data from file
    FILE *fptr1 = fopen("unsorted.txt", "r");
    if (!fptr1)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    int inputs[MAX];
    int n = 0;
    while (fscanf(fptr1, "%d", &inputs[n]) == 1 && n < MAX)
    {
        n++;
    }
    fclose(fptr1);

    int step_size;
    printf("Enter number of steps: ");
    scanf("%d", &step_size);
    int steps[MAXSTEPS];
    printf("Enter inputs for each step: ");
    for (int i = 0; i < step_size && i < MAXSTEPS; i++)
    {
        scanf("%d", &steps[i]);
    }

    // Get the comparisons for unsorted data (Average Case)
    printf("Comparisons to sort unsorted data (Insertion Sort)\n");
    double *avg_cmp = compare_inputs(inputs, steps, step_size);

    // Sort the entire input array
    insertionSort(inputs, n);

    // Get the comparisons for sorted data (Best Case)
    printf("Comparisons to sort sorted data (Insertion Sort)\n");
    double *best_cmp = compare_inputs(inputs, steps, step_size);

    write_to_csv(steps, avg_cmp, best_cmp, step_size);

    free(avg_cmp);
    free(best_cmp);

    // Average case comparisons = n^2
    // Best case comparisons = n
    return 0;
}