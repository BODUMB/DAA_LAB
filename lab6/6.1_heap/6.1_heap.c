#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
    int id;
    char name[100];
    int age;
    int height;
    int weight;
};

void read_file(const char *filename, struct person arr[], int *n) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", n); // Read the number of persons from file

    for (int i = 0; i < *n; i++) {
        fscanf(file, "%d %s %d %d %d", &arr[i].id, arr[i].name, &arr[i].age, &arr[i].height, &arr[i].weight);
    }

    fclose(file);
}

void swap(struct person *x, struct person *y) {
    struct person temp = *x;
    *x = *y;
    *y = temp;
}

void min_heapify_age(struct person arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Find the smallest among root, left child, and right child
    if (left < n && arr[left].age < arr[smallest].age)
        smallest = left;

    if (right < n && arr[right].age < arr[smallest].age)
        smallest = right;

    // Swap and continue heapifying if root is not the smallest
    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        min_heapify_age(arr, n, smallest); // Only recurse if a swap happened
    }
}

void build_min_heap_age(struct person arr[], int n) {
    // Building the heap by heapifying from the last non-leaf node to the root
    for (int i = n / 2 - 1; i >= 0; i--) {
        min_heapify_age(arr, n, i);
    }
}

void max_heapify_weight(struct person arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Find the largest among root, left child, and right child
    if (left < n && arr[left].weight > arr[largest].weight)
        largest = left;

    if (right < n && arr[right].weight > arr[largest].weight)
        largest = right;

    // Swap and continue heapifying if root is not the largest
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        max_heapify_weight(arr, n, largest);
    }
}

void build_max_heap_weight(struct person arr[], int n) {
    // Building the heap by heapifying from the last non-leaf node to the root
    for (int i = n / 2 - 1; i >= 0; i--) {
        max_heapify_weight(arr, n, i);
    }
}

void display_youngest_weight(struct person arr[], int n) {
    printf("Weight of youngest person: %.2f kg\n", arr[0].weight * 0.453592); // Convert pounds to kg
}

void insert_min_heap(struct person arr[], int *n, struct person new_person) {
    arr[*n] = new_person;
    int i = *n;
    (*n)++;
    while (i != 0 && arr[(i - 1) / 2].age > arr[i].age) {
        swap(&arr[i], &arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void delete_oldest_person(struct person arr[], int *n) {
    if (*n <= 0) {
        printf("Heap is empty\n");
        return;
    }

    arr[0] = arr[*n - 1];
    (*n)--;
    min_heapify_age(arr, *n, 0);
}

void menu() {
    printf("MAIN MENU (HEAP)\n");
    printf("1. Read Data\n");
    printf("2. Create a Min-heap based on the age\n");
    printf("3. Create a Max-heap based on the weight\n");
    printf("4. Display weight of the youngest person\n");
    printf("5. Insert a new person into the Min-heap\n");
    printf("6. Delete the oldest person\n");
    printf("7. Exit\n");
}

int main() {
    struct person *arr = NULL;
    int n = 0;
    int choice;

    arr = (struct person *)malloc(50 * sizeof(struct person)); // Assuming max 50 people in file

    while (1) {
        menu();
        printf("Enter option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                read_file("rand.dat", arr, &n);
                printf("Data read successfully.\n");
                break;
            case 2:
                build_min_heap_age(arr, n);
                printf("Min-heap created based on age.\n");
                break;
            case 3:
                build_max_heap_weight(arr, n);
                printf("Max-heap created based on weight.\n");
                break;
            case 4:
                if (n > 0) {
                    display_youngest_weight(arr, n);
                } else {
                    printf("Heap is empty.\n");
                }
                break;
            case 5: {
                struct person new_person;
                printf("Enter new person data (id name age height weight): ");
                scanf("%d %s %d %d %d", &new_person.id, new_person.name, &new_person.age, &new_person.height, &new_person.weight);
                insert_min_heap(arr, &n, new_person);
                printf("New person inserted into the Min-heap.\n");
                break;
            }
            case 6:
                delete_oldest_person(arr, &n);
                printf("Oldest person deleted from the Min-heap.\n");
                break;
            case 7:
                free(arr);
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    }

    return 0;
}
