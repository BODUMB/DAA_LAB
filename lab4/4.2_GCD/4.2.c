#include <stdio.h>
#include <stdlib.h>

// Recursive function to calculate GCD of two numbers
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open source file for reading
    FILE *src = fopen(argv[1], "r");
    if (src == NULL) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Open destination file for writing
    FILE *dst = fopen(argv[2], "w");
    if (dst == NULL) {
        perror("Error opening destination file");
        fclose(src);
        exit(EXIT_FAILURE);
    }

    int num1, num2;
    while (fscanf(src, "%d %d", &num1, &num2) == 2) {
        int result = gcd(num1, num2);
        fprintf(dst, "The GCD of %d and %d is %d\n", num1, num2, result);
    }

    fclose(src);
    fclose(dst);

    printf("GCDs have been calculated and stored in %s\n", argv[2]);

    return 0;
}
