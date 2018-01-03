#include <algorithm>
#include <iostream>
#include <limits.h>
#include <math.h>
#include <queue>
#include <stdio.h>
int *mod;
using namespace std;

bool check(int *d, long long mid, int n, long long k) {
    long long x = 0;
    for (int i = 0; i < n; ++i) {
        x += ceil(1.0 * mid / d[i]);
    }
    return x < k;
}
long long summax(int *d, int n, long long k) {
    long long s = 0;
    int max = 0;
    for (int i = 0; i < n; ++i) {
        if (d[i] > max) {
            max = d[i];
        }
    }
    return max * k;
}
int main(int argc, char const *argv[]) {
    FILE *f = freopen(argv[1], "r", stdin);
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long k;
    int n;
    cin >> n >> k;
    int d[n];
    mod = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> d[i];
    }

    long long low = 0;
    long long high = summax(d, n, k) / n;
    long long mid;
    while (low < high) {
        mid = low + (high - low) / 2;
        if (check(d, mid, n, k)) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    long long x = 0;
    for (int i = 0; i < n; ++i) {
        x += ceil(1.0 * low / d[i]);

        mod[i] = low % d[i];
        // cout << mod[i] <<  endl;
    }
    int index = 0;
    long long difference = x - k;
    for (int i = n - 1; i >= 0; --i) {
        if ((d[i] == 1 ? mod[i] == 0 : mod[i] == 1)) {
            if (difference > 0) {
                difference--;
                continue;
            }
            index = i;
            break;
        }
    }
    low += d[index] - 1;
    cout << index + 1 << " " << low << endl;
    return 0;
}