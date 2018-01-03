#include <iostream>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#define min(a, b) ((a) > (b) ? (b) : (b))
int **E;
int **cost;
using namespace std;
inline int sumQuery(int **aux, int tli, int tlj, int rbi, int rbj) {
    return aux[rbi][rbj] - aux[tli - 1][rbj] - aux[rbi][tlj - 1] +
           aux[tli - 1][tlj - 1];
}

void compute(int start, int end, int newl[], int oldl[], int startold,
             int endold) {
    // cout << "start= "<< start << " end= " << end << endl;
    int mid = (end + start) / 2;
    if (start >= end) {
        return;
    }
    int midnew;
    int c;
    newl[mid] = INT_MAX;
    for (int i = startold; i < endold; ++i) {

        c = oldl[i] + sumQuery(cost, i + 1, i + 1, mid, mid);

        if (newl[mid] > c) {
            newl[mid] = c;
            midnew = i;
        }
    }
    compute(start, mid, newl, oldl, startold, midnew + 1);
    compute(mid + 1, end, newl, oldl, midnew, endold);
}
void partition(int **cost, int N, int K) {

    int n = N;
    E = (int **)malloc((K + 1) * sizeof(int *));
    for (int i = 0; i <= N; i++)
        E[i] = (int *)malloc((N + 1) * sizeof(int));

    E[0][0] = 0;
    for (int i = 1; i < N + 1; ++i) {
        E[1][i] = cost[i][i];
    }
    E[1][1] = 0;
    for (int i = 1; i < K + 1; ++i) {
        E[i][1] = 0;
    }
    for (int i = 2; i < K + 1; ++i) {
        compute(1, N + 1, E[i], E[i - 1], 1, N + 1);
    }
    cout << E[K][N] << endl;
}

int preProcess(int **mat, int **aux, int N) {
    for (int i = 0; i < N; i++)
        aux[0][i] = mat[0][i];

    for (int i = 1; i < N; i++)
        for (int j = 0; j < N; j++)
            aux[i][j] = mat[i][j] + aux[i - 1][j];

    for (int i = 0; i < N; i++)
        for (int j = 1; j < N; j++)
            aux[i][j] += aux[i][j - 1];
}

int main(int argc, char const *argv[]) {
    FILE *f = freopen(argv[1], "r", stdin);
    int N, K;
    std::ios_base::sync_with_stdio(false);
    cin >> N >> K;
    int **A = (int **)malloc((N + 1) * sizeof(int *));
    for (int i = 0; i <= N; i++)
        A[i] = (int *)calloc((N + 1), sizeof(int));
    // return 0;

    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            cin >> A[i + 1][j + 1];
        }
    }
    cost = (int **)malloc((N + 1) * sizeof(int *));
    for (int i = 0; i <= N; i++)
        cost[i] = (int *)calloc((N + 1), sizeof(int));

    preProcess(A, cost, N + 1);
    for (int i = 0; i <= N; ++i) {
        free(A[i]);
    }
    partition(cost, N, K);

    return 0;
}