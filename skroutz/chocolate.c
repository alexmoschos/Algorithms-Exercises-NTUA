#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#define max(a, b) ((a) > (b) ? (a) : (b))

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int *prices = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        scanf("%d", &prices[i]);
    }
    k *= 2;
    int *carry1 = (int *)calloc((k + 1), sizeof(int));
    int *carry0 = (int *)calloc((k + 1), sizeof(int));
    carry1[0] = -INT_MAX;
    for (int i = 0; i <= k; ++i) {
        carry1[i] = -prices[0];
    }
    for (int i = 1; i < n; ++i) {
        for (int j = k; j >= 1; --j) {
            carry1[j] = max(carry1[j], carry0[j - 1] - prices[i]);
            carry0[j] = max(carry0[j], carry1[j - 1] + prices[i]);
        }
    }
    printf("%d", carry0[k]);
    return 0;
}