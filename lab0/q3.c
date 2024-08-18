// print sum of n nos using recursion

#include <stdio.h>

// Recursive function to calculate the sum of first n natural numbers
int sumOfNumbers(int n) {
    if (n <= 0) {
        return 0;
    }
    return n + sumOfNumbers(n - 1);
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    scanf("%d", &n);

    int result = sumOfNumbers(n);
        printf("Sum of the first %d natural numbers is: %d\n", n, result);
    return 0;
}
