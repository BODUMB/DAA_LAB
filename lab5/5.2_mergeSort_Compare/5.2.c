#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10000
#define MAXSTEPS 20

long long comparisons = 0;

void merge(int arr[], int l, int mid, int r)
{
    int i = l, j = mid + 1;
    int k = 0;
    int size = r - l + 1;
    int *temp = (int *)malloc(size * sizeof(int));

    while (i <= mid && j <= r) // Merge the two halves into temp array
    {
        comparisons++;
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= r)
        temp[k++] = arr[j++];

    for (int p = 0; p < size; p++)
        arr[l + p] = temp[p];

    free(temp);
}

void merge_sort(int arr[], int l, int r)
{
    if (l < r)
    {
        int mid = l + (r - l) / 2;
        merge_sort(arr, l, mid);
        merge_sort(arr, mid + 1, r);
        merge(arr, l, mid, r);
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
        merge_sort(temp, 0, n - 1);
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
    printf("Comparisons to sort unsorted data (Merge Sort)\n");
    double *avg_cmp = compare_inputs(inputs, steps, step_size);

    // Sort the entire input array
    merge_sort(inputs, 0, n - 1);

    // Get the comparisons for sorted data (Best Case)
    printf("Comparisons to sort sorted data (Merge Sort)\n");
    double *best_cmp = compare_inputs(inputs, steps, step_size);

    write_to_csv(steps, avg_cmp, best_cmp, step_size);

    free(avg_cmp);
    free(best_cmp);

    // Average / Best Case comparisons = n * log (n) - n + 1
    return 0;
}