#include <stdio.h>
#include <string.h>

// Function to find the length of the Longest Common Subsequence (LCS)
int lcs(char *str1, char *str2, int m, int n) {
    int dp[m + 1][n + 1];  // DP table to store LCS lengths

    // Build the dp table in a bottom-up manner
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;  // LCS of an empty string with any string is 0
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;  // If characters match, add 1 to the previous diagonal
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];  // Otherwise, take max of top or left cell
            }
        }
    }

    // Length of LCS is stored at dp[m][n]
    return dp[m][n];
}

// // Function to print the LCS itself
// void print_lcs(char *str1, char *str2, int m, int n) {
//     int dp[m + 1][n + 1];

//     // Build the dp table (same as before)
//     for (int i = 0; i <= m; i++) {
//         for (int j = 0; j <= n; j++) {
//             if (i == 0 || j == 0) {
//                 dp[i][j] = 0;
//             } else if (str1[i - 1] == str2[j - 1]) {
//                 dp[i][j] = dp[i - 1][j - 1] + 1;
//             } else {
//                 dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
//             }
//         }
//     }

//     // Now retrieve the LCS from the dp table
//     int index = dp[m][n];  // Length of LCS
//     char lcs[index + 1];
//     lcs[index] = '\0';  // Null-terminate the string

//     // Start from dp[m][n] and trace back the path
//     int i = m, j = n;
//     while (i > 0 && j > 0) {
//         if (str1[i - 1] == str2[j - 1]) {  // If characters match, they are part of the LCS
//             lcs[index - 1] = str1[i - 1];
//             i--;
//             j--;
//             index--;
//         } else if (dp[i - 1][j] > dp[i][j - 1]) {
//             i--;  // Move up in the table
//         } else {
//             j--;  // Move left in the table
//         }
//     }

//     // Print the LCS
//     printf("Longest Common Subsequence: %s\n", lcs);
// }

int main() {
    char str1[100], str2[100];

    // Input two strings
    printf("Enter the first string: ");
    scanf("%s", str1);
    printf("Enter the second string: ");
    scanf("%s", str2);

    int m = strlen(str1);
    int n = strlen(str2);

    // Find and print the length of LCS
    int length = lcs(str1, str2, m, n);
    printf("Length of Longest Common Subsequence: %d\n", length);

    // Print the LCS itself
    // print_lcs(str1, str2, m, n);

    return 0;
}
