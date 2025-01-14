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

void load_unsorted_data(int inputs[], int *n)
{
    FILE *fptr1 = fopen("unsorted.txt", "r");
    if (!fptr1)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    *n = 0;
    while (fscanf(fptr1, "%d", &inputs[*n]) == 1 && *n < MAX)
        (*n)++;

    fclose(fptr1);
}

void perform_comparisons(int inputs[], int n, int steps[], int step_size)
{
    printf("Comparisons to sort unsorted data (QuickSort)\n");
    double *avg_cmp = compare_inputs(inputs, steps, step_size);

    // Sort the entire input array
    quickSort(inputs, 0, n - 1);

    printf("Comparisons to sort sorted data (QuickSort)\n");
    double *worst_cmp = compare_inputs(inputs, steps, step_size);

    write_to_csv(steps, avg_cmp, worst_cmp, step_size);

    free(avg_cmp);
    free(worst_cmp);
}

int main()
{
    int inputs[MAX];
    int n = 0;
    int step_size;
    int steps[MAXSTEPS];
    int choice;

    while (1)
    {
        // Display menu
        printf("\nMenu:\n");
        printf("1. Load unsorted data\n");
        printf("2. Enter step sizes and perform comparisons\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            // Load unsorted data from file
            load_unsorted_data(inputs, &n);
            printf("Unsorted data loaded successfully.\n");
            break;

        case 2:
            // Check if data is loaded
            if (n == 0)
            {
                printf("No data loaded. Please load unsorted data first.\n");
                break;
            }

            // Enter number of steps and input sizes for testing
            printf("Enter number of steps: ");
            scanf("%d", &step_size);
            printf("Enter inputs for each step: ");
            for (int i = 0; i < step_size && i < MAXSTEPS; i++)
                scanf("%d", &steps[i]);

            // Perform comparisons and write results to CSV
            perform_comparisons(inputs, n, steps, step_size);
            break;

        case 3:
            // Exit the program
            printf("Exiting the program.\n");
            exit(0);

        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
