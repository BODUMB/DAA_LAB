#include <stdio.h>
#include <stdlib.h>

#define MAX 10000
#define MAXSTEPS 20

long long comparisons = 0;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int array[], int l, int r)
{
    int pivot = array[r];
    int i = (l - 1);
    for (int j = l; j < r; j++)
    {
        comparisons++;
        if (array[j] <= pivot)
        {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[r]);
    return (i + 1);
}

void quickSort(int array[], int l, int r)
{
    if (l < r)
    {
        int pi = partition(array, l, r);
        quickSort(array, l, pi - 1);
        quickSort(array, pi + 1, r);
    }
}

double *compare_inputs(int inputs[], int steps[], int size)
{
    double *cmp_arr = (double *)malloc(size * sizeof(double));
    for (int k = 0; k < size; k++)
    {
        int n = steps[k];
        comparisons = 0;
        int *temp = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
            temp[i] = inputs[i];
        quickSort(temp, 0, n - 1);
        cmp_arr[k] = comparisons;
        printf("%d elements: %lld\n", n, comparisons);
        free(temp);
    }
    printf("\n");
    return cmp_arr;
}

void write_to_csv(int steps[], double avg_cmp[], double worst_cmp[], int size)
{
    FILE *file = fopen("data.csv", "w");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "Input Size,Avg Case Comparisons,worst Case Comparisons\n");
    for (int i = 0; i < size; i++)
        fprintf(file, "%d,%lf,%lf\n", steps[i], avg_cmp[i], worst_cmp[i]);
    fclose(file);
}

int main()
{
    FILE *fptr1 = fopen("unsorted.txt", "r");
    if (!fptr1)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    int inputs[MAX];
    int n = 0;
    while (fscanf(fptr1, "%d", &inputs[n]) == 1 && n < MAX)
        n++;

    fclose(fptr1);

    int step_size;
    printf("Enter number of steps: ");
    scanf("%d", &step_size);
    int steps[MAXSTEPS];
    printf("Enter inputs for each step: ");
    for (int i = 0; i < step_size && i < MAXSTEPS; i++)
        scanf("%d", &steps[i]);

    printf("Comparisons to sort unsorted data (QuickSort)\n");
    double *avg_cmp = compare_inputs(inputs, steps, step_size);

    // Sort the entire input array
    quickSort(inputs, 0, n - 1);

    printf("Comparisons to sort sorted data (QuickSort)\n");
    double *worst_cmp = compare_inputs(inputs, steps, step_size);

    write_to_csv(steps, avg_cmp, worst_cmp, step_size);

    free(avg_cmp);
    free(worst_cmp);

    return 0;
}