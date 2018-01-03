#include <algorithm>
#include <iostream>
#include <limits.h>
#include <math.h>
#include <queue>
#include <stack>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
#define max(a, b) ((a) > (b) ? (a) : (b))
struct edge_node_t {
    int x;
    int y;
    int w;
    bool operator<(struct edge_node_t other) const { return w < other.w; }
    struct edge_node_t *left = NULL;
    struct edge_node_t *right = NULL;
    int id;
};
struct subset_t {
    int parent;
    int rank;
    struct edge_node_t *node = NULL;
};
typedef struct subset_t subset;
subset *A;
typedef struct edge_node_t edge_node;

int find(int x) {
    if (x != A[x].parent) {
        A[x].parent = find(A[x].parent);
    }
    return A[x].parent;
}
void Union(int x, int y, int w) {
    int xr = find(x);
    int yr = find(y);
    edge_node *e = new edge_node();
    e->x = x;
    e->y = y;
    e->left = A[xr].node;
    e->right = A[yr].node;
    e->w = w;
    if (A[xr].rank < A[yr].rank) {
        A[xr].parent = yr;
        A[yr].node = e;
    } else if (A[xr].rank == A[yr].rank) {
        A[yr].parent = xr;
        A[xr].rank++;
        A[xr].node = e;
    } else {
        A[yr].parent = xr;
        A[xr].node = e;
    }
}

int idcounter = 0;
int *position;
int *L;
int *euler;
int *we;
int **P;
int lognmax;
int ind = 0;
int *firstOccurrence;
void inorder(edge_node *root, int parent, int level) {
    if (root == NULL)
        return;
    root->id = idcounter++;
    euler[ind] = root->id;
    ind++;
    if (firstOccurrence[root->id] == -1) {
        firstOccurrence[root->id] = ind - 1;
    }
    position[root->x] = root->id;
    position[root->y] = root->id;
    L[root->id] = level;
    we[root->id] = root->w;
    if (root->left) {
        inorder(root->left, root->id, level + 1);
        euler[ind] = root->id;
        ind++;
    }
    if (root->right) {
        inorder(root->right, root->id, level + 1);
        euler[ind] = root->id;
        ind++;
    }
}
void preprocess(int arr[], int n) {
    // Initialize M for the intervals with length 1
    for (int i = 0; i < n; i++)
        P[i][0] = i;

    // Compute values from smaller to bigger intervals
    for (int j = 1; (1 << j) <= n; j++) {
        // Compute minimum value for all intervals with size 2^j
        for (int i = 0; (i + (1 << j) - 1) < n; i++) {
            // For arr[2][10], we compare arr[P[0][7]] and
            // arr[P[3][10]]
            if (arr[P[i][j - 1]] < arr[P[i + (1 << (j - 1))][j - 1]])
                P[i][j] = P[i][j - 1];
            else
                P[i][j] = P[i + (1 << (j - 1))][j - 1];
        }
    }
}
int query(int arr[], int L, int R) {
    int j = (int)log2(R - L + 1);

    if (arr[P[L][j]] <= arr[P[R - (int)pow(2, j) + 1][j]])
        return arr[P[L][j]];

    else
        return arr[P[R - (int)pow(2, j) + 1][j]];
}
int main(int argc, char const *argv[]) {
    int n, m, x, y, w;
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    edge_node *edge = new edge_node[m];
    for (int i = 0; i < m; ++i) {
        cin >> x >> y >> w;
        x--;
        y--;
        edge_node e;
        e.x = x;
        e.y = y;
        e.w = w;
        edge[i] = e;
    }
    sort(edge, edge + m);
    int i = 0;
    int j = 0;
    // vector< edge_node > result(n-1);
    A = new subset[n];
    edge_node e, e1;
    for (int i = 0; i < n; ++i) {
        A[i].parent = i;
        A[i].rank = 0;
    }
    while (i < n - 1) {
        e = edge[j];
        if (find(e.x) != find(e.y)) {
            i++;
            e1 = e;
            Union(e.x, e.y, e.w);
        }
        j++;
    }
    delete edge;
    int Q;
    cin >> Q;

    position = new int[n];
    firstOccurrence = new int[n];
    for (int i = 0; i < n; ++i) {
        firstOccurrence[i] = -1;
    }
    we = new int[n];
    n--;
    n = 2 * n - 1;
    lognmax = log2(n);
    // cout << "hello" << endl;
    P = new int *[n];
    // cout << "hi";
    for (int i = 0; i < n; ++i) {
        P[i] = new int[lognmax];
    }

    euler = new int[n];
    L = new int[n];

    inorder(A[find(e1.x)].node, -1, 0);
    preprocess(euler, n);

    for (int i = 0; i < Q; ++i) {
        cin >> x >> y;
        x--;
        y--;
        // cout << i << endl;
        int aa = firstOccurrence[position[x]];
        int bb = firstOccurrence[position[y]];
        if (aa > bb) {
            int temp = aa;
            aa = bb;
            bb = temp;
        }
        printf("%d\n", we[query(euler, aa, bb)]);
    }

    return 0;
}