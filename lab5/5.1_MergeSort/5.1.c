#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long comparisons = 0;

void merge(int arr[], int l, int mid, int r) {
    int i = l, j = mid + 1;
    int k = 0;
    int size = r - l + 1;
    int *temp = (int *)malloc(size * sizeof(int));

    while (i <= mid && j <= r) {
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

void merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int mid = l + (r - l) / 2;
        merge_sort(arr, l, mid);
        merge_sort(arr, mid + 1, r);
        merge(arr, l, mid, r);
    }
}

void read_file(const char *filename, int arr[], int *n) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    *n = 0;
    while (fscanf(file, "%d", &arr[*n]) == 1) {
        (*n)++;
    }
    fclose(file);
}

void write_file(const char *filename, int arr[], int n) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", arr[i]);
    }
    fclose(file);
}

void display_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void menu() {
    printf("MAIN MENU (MERGE SORT)\n");
    printf("1. Ascending Data\n");
    printf("2. Descending Data\n");
    printf("3. Random Data\n");
    printf("4. ERROR (EXIT)\n");
}

int main() {
    int choice;
    int arr[500];
    int n;
    clock_t start, end;
    double elapsed_time;
    
    while (1) {
        menu();
        printf("Enter option: ");
        scanf("%d", &choice);
        comparisons = 0;

        switch (choice) {
            case 1:
                read_file("inAsce.dat", arr, &n);
                printf("Before Sorting (Ascending Order): ");
                display_array(arr, n);

                start = clock();
                merge_sort(arr, 0, n - 1);
                end = clock();

                printf("After Sorting: ");
                display_array(arr, n);
                write_file("outMergeAsce.dat", arr, n);
                break;

            case 2:
                read_file("inDesc.dat", arr, &n);
                printf("Before Sorting (Descending Order): ");
                display_array(arr, n);

                start = clock();
                merge_sort(arr, 0, n - 1);
                end = clock();

                printf("After Sorting: ");
                display_array(arr, n);
                write_file("outMergeDesc.dat", arr, n);
                break;

            case 3:
                read_file("inRand.dat", arr, &n);
                printf("Before Sorting (Random Data): ");
                display_array(arr, n);

                start = clock();
                merge_sort(arr, 0, n - 1);
                end = clock();

                printf("After Sorting: ");
                display_array(arr, n);
                write_file("outMergeRand.dat", arr, n);
                break;

            case 4:
                printf("Exiting program...\n");
                exit(0);

            default:
                printf("Invalid option! Please try again.\n");
                continue;
        }

        // Calculate execution time
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1e9; // Convert to nanoseconds
        printf("Number of Comparisons: %lld\n", comparisons);
        printf("Execution Time: %.2f nanoseconds\n", elapsed_time);
        printf("\n");
    }

    return 0;
}
