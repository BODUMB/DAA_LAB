// add digits of a no using recursion

#include <stdio.h>

// Recursive function to add the digits of a number
int sumOfDigits(int n) {
    if (n == 0) {
        return 0;
    }
    return (n % 10) + sumOfDigits(n / 10);
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    int result = sumOfDigits(number);
    printf("Sum of digits of %d is: %d\n", number, result);

    return 0;
}
