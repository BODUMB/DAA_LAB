// reverse a given no using recursion

#include <stdio.h>

// Helper function to perform the reverse calculation
int reverseNumberHelper(int n, int reversed) {
    if (n == 0) {
        return reversed;
    }
    reversed = (reversed * 10) + (n % 10);
    return reverseNumberHelper(n / 10, reversed);
}


int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    int reversed = reverseNumberHelper(number,0);
    printf("Reversed number: %d\n", reversed);

    return 0;   
}

