#include <iostream>
#include <stdlib.h>

#include <stdio.h>

using namespace std;

int count1 = 0;
int main(int argc, char const *argv[]) {
    FILE *f = freopen(argv[1], "r", stdin);
    int n, k;
    cin >> n >> k;
    int a[n][n];
    int b[n + 1][n];
    int c[n];
    getchar();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = getchar() - '0';
        }
        getchar();
    }

    for (int j = 0; j < n; ++j) {
        for (int i = 0; i <= n; ++i) {
            if (i == 0) {
                b[i][j] = 0;
                continue;
            }
            b[i][j] = b[i - 1][j] + a[i - 1][j];
        }
    }

    for (int p = 0; p <= n; ++p) {
        for (int q = p + 1; q <= n; ++q) {
            c[0] = b[q][0] - b[p][0];
            for (int j = 1; j < n; ++j) {
                c[j] = c[j - 1] + b[q][j] - b[p][j];
            }

            int l = 0;
            int r = 0;
            while (r < n) {
                if (c[r] - c[l] == k) {
                    ++count1;
                    int newl = l + 1;
                    while (c[r] - c[newl] == k) {
                        ++count1;
                        newl++;
                    }
                    r++;
                } else if (c[r] - c[l] > k)
                    l++;
                else
                    r++;
            }
            for (int i = 0; i < n; ++i) {
                if (c[i] == k)
                    count1++;
            }
        }
    }
    cout << count1 << endl;
    return 0;
}