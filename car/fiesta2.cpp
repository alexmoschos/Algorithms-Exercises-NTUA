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
int *we;
int **P;
int lognmax;
void inorder(edge_node *root, int parent, int level) {
    if (root == NULL)
        return;
    root->id = idcounter++;
    P[0][root->id] = parent;
    position[root->x] = root->id;
    position[root->y] = root->id;
    L[root->id] = level;
    we[root->id] = root->w;

    inorder(root->left, root->id, level + 1);
    inorder(root->right, root->id, level + 1);
}
void dynamic(int n, int **P) {

    for (int i = 1; i < lognmax; ++i) {
        for (int j = 0; j < n; ++j) {
            if (P[i - 1][j] != -1)
                P[i][j] = P[i - 1][P[i - 1][j]];
        }
    }
}
int getparent(int u, int v) {
    for (int i = 0; i < lognmax; ++i) {
        if (v & 1)
            u = P[i][u];
        v >>= 1;
    }
    return u;
}
int findancestor(int n, int u, int v) {
    if (L[u] > L[v]) {
        u = getparent(u, L[u] - L[v]);
    } else if (L[v] > L[u]) {
        v = getparent(v, L[v] - L[u]);
    }

    if (u == v)
        return u;
    for (int i = lognmax - 1; i >= 0; --i) {
        if (P[i][u] != P[i][v]) {
            u = P[i][u];
            v = P[i][v];
        }
    }
    return P[0][u];
}
int main(int argc, char const *argv[]) {
    int n, m, x, y, w;
    std::ios_base::sync_with_stdio(false);
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
            // result[i++] = e;
            i++;
            e1 = e;
            // cout << e.x << " " << e.y << " " << e.w << endl;
            Union(e.x, e.y, e.w);
        }
        j++;
    }
    delete edge;
    int Q;
    cin >> Q;

    int log = log2(n - 1) + 1;
    lognmax = log;
    position = new int[n];
    L = new int[n];
    we = new int[n];

    P = new int *[log];
    for (int i = 0; i < log; ++i) {
        P[i] = new int[n - 1];
        for (int j = 0; j < n - 1; ++j) {
            P[i][j] = -1;
        }
    }
    inorder(A[find(e1.x)].node, -1, 0);
    delete A;
    dynamic(n - 1, P);
    int a[Q];
    int b[Q];
    for (int i = 0; i < Q; ++i) {
        cin >> x >> y;
        x--;
        y--;
        a[i] = x;
        b[i] = y;
    }
    for (int i = 0; i < Q; ++i) {
        int z = findancestor(n - 1, position[a[i]], position[b[i]]);
        printf("%d\n", we[z]);
    }
    return 0;
}