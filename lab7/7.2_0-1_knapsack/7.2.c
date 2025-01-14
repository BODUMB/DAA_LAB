#include <stdio.h>
#include <stdlib.h>

struct ITEM {
    int item_id;
    int item_profit;
    int item_weight;
    float prof 1it_weight_ratio;
};

// Function to swap two items
void swap(struct ITEM *x, struct ITEM *y) {
    struct ITEM temp = *x;
    *x = *y;
    *y = temp;
}

// Function to perform heapify operation for sorting based on profit/weight ratio
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

// Function to build heap
void heapSort(struct ITEM arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

// Function to calculate the maximum profit for the 0/1 knapsack problem
float knapsack(struct ITEM items[], int n, int capacity) {
    float dp[capacity + 1];
    
    // Initialize the dp array 
    for (int w = 0; w <= capacity; w++) {
        dp[w] = 0;
    }

    // Fill the dp array using the items
    for (int i = 0; i < n; i++) {
        for (int w = capacity; w >= items[i].item_weight; w--) {
            dp[w] = (dp[w] > dp[w - items[i].item_weight] + items[i].item_profit) ? 
                      dp[w] : 
                      dp[w - items[i].item_weight] + items[i].item_profit;
        }
    }

    // Print the items taken
    printf("Item No\tProfit\tWeight\tAmount to be taken\n");
    int max_profit = dp[capacity];
    for (int i = n - 1, w = capacity; i >= 0 && max_profit > 0; i--) {
        if (max_profit != dp[w]) { // This means the item was included
            printf("%d\t%d\t%d\t1.000000\n", items[i].item_id, items[i].item_profit, items[i].item_weight);
            max_profit -= items[i].item_profit;
            w -= items[i].item_weight;
        }
    }

    return dp[capacity];
}

int main() {
    int n;
    printf("Enter the number of items: ");
    scanf("%d", &n);

    struct ITEM *items = (struct ITEM *)malloc(n * sizeof(struct ITEM));

    for (int i = 0; i < n; i++) {
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%d %d", &items[i].item_profit, &items[i].item_weight);
        items[i].item_id = i + 1;
        items[i].profit_weight_ratio = (float)items[i].item_profit / items[i].item_weight;
    }

    int capacity;
    printf("Enter the capacity of the knapsack: ");
    scanf("%d", &capacity);

    // Sort the items based on profit/weight ratio in non-increasing order
    heapSort(items, n);

    // Calculate and print the maximum profit
    float max_profit = knapsack(items, n, capacity);
    printf("Maximum profit: %.6f\n", max_profit);

    free(items);
    return 0;
}
