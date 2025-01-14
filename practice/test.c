#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}
int knap(int W, int v[], int w[], int n) {
    int dp[n + 1][W + 1];

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0; 
            } else if (w[i - 1] <= j) {
                dp[i][j] = max(v[i - 1] + dp[i - 1][j - w[i - 1]], dp[i - 1][j]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return dp[n][W];
}

int main() {
    int v[] = {2, 3, 4, 5};
    int w[] = {3, 4, 5, 6}; 
    int W = 5; 
    int n = sizeof(v) / sizeof(v[0]); 
    printf("Max profit with weight capacity %d is %d\n", W, knap(W, v, w, n));
    return 0;
}
