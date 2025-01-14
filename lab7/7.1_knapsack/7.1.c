#include <stdio.h>
#include <stdlib.h>

struct ITEM {
    int item_id;
    float item_profit;
    float item_weight;
    float profit_weight_ratio;
};

// Function to swap two items
void swap(struct ITEM* a, struct ITEM* b) {
    struct ITEM temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify function to maintain the max-heap property based on profit/weight ratio
void heapify(struct ITEM arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].profit_weight_ratio > arr[largest].profit_weight_ratio)
        largest = left;

    if (right < n && arr[right].profit_weight_ratio > arr[largest].profit_weight_ratio)
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// Function to build a max heap
void build_max_heap(struct ITEM arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

// Heap sort function to sort items based on profit/weight ratio in non-increasing order
void heap_sort(struct ITEM arr[], int n) {
    build_max_heap(arr, n);
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

// Function to calculate the maximum profit
float fractional_knapsack(struct ITEM arr[], int n, float capacity) {
    // Sorting items by profit/weight ratio using heap sort
    heap_sort(arr, n);
    
    float total_profit = 0.0;
    
    for (int i = n - 1; i >= 0; i--) {
        if (capacity >= arr[i].item_weight) {
            capacity -= arr[i].item_weight;
            total_profit += arr[i].item_profit;
            printf("Item %d %.6f %.6f 1.000000\n", arr[i].item_id, arr[i].item_profit, arr[i].item_weight);
        } else {
            float fraction = capacity / arr[i].item_weight;
            total_profit += arr[i].item_profit * fraction;
            printf("Item %d %.6f %.6f %.6f\n", arr[i].item_id, arr[i].item_profit, arr[i].item_weight, fraction);
            break;
        }
    }
    
    return total_profit;
}

int main() {
    int n;
    float capacity;

    // Input the number of items
    printf("Enter the number of items: ");
    scanf("%d", &n);

    struct ITEM items[n];

    // Input the profit and weight of each item
    for (int i = 0; i < n; i++) {
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%f %f", &items[i].item_profit, &items[i].item_weight);
        items[i].item_id = i + 1;
        items[i].profit_weight_ratio = items[i].item_profit / items[i].item_weight;
    }

    // Input the knapsack capacity
    printf("Enter the capacity of knapsack: ");
    scanf("%f", &capacity);

    // Calculate the maximum profit and print the result
    float max_profit = fractional_knapsack(items, n, capacity);
    printf("Maximum profit: %.6f\n", max_profit);

    return 0;
}
