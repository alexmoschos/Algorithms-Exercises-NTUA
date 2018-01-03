#include <algorithm>
#include <iostream>
#include <limits.h>
#include <queue>
#include <stack>
#include <stdio.h>
#include <vector>
using namespace std;
#define max(a, b) ((a) > (b) ? (a) : (b))

typedef pair<int, int> intpair;
struct edge_node_t {
    int x;
    int y;
    int w;
    bool operator<(struct edge_node_t other) const { return w < other.w; }
};
struct subset_t {
    int parent;
    int rank;
};
typedef struct subset_t subset;
subset *A;
typedef struct edge_node_t edge_node;
class graph {
  public:
    vector<pair<int, int>> *adj;
    int n;
    int m;
    graph(int n, int m) {
        this->n = n;
        this->m = m;
        adj = new vector<pair<int, int>>[n];
    }
    ~graph();
    void addedge(int u, int v, int w) {
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
};
int find(int x) {
    if (x != A[x].parent) {
        A[x].parent = find(A[x].parent);
    }
    return A[x].parent;
}
void Union(int x, int y) {
    int xr = find(x);
    int yr = find(y);
    if (A[xr].rank < A[yr].rank)
        A[xr].parent = yr;
    else if (A[xr].rank == A[yr].rank) {
        A[yr].parent = xr;
        A[xr].rank++;
    } else {
        A[yr].parent = xr;
    }
}
void dfs(graph *g, int start, int *result) {
    bool *visited = new bool[g->n];
    int current;
    for (int i = 0; i < g->n; ++i) {
        visited[i] = false;
    }
    stack<intpair> q;
    q.push(make_pair(start, 0));
    while (!q.empty()) {
        current = q.top().first;
        result[current] = q.top().second;
        q.pop();
        if (!visited[current])
            visited[current] = true;
        for (intpair next : g->adj[current]) {
            if (!visited[next.first]) {
                q.push(
                    make_pair(next.first, max(result[current], next.second)));
            }
        }
    }
}
int main(int argc, char const *argv[]) {
    int n, m, x, y, w;
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    graph *g = new graph(n, m);
    vector<edge_node> edge(m);
    for (int i = 0; i < m; ++i) {
        cin >> x >> y >> w;
        x--;
        y--;
        g->addedge(x, y, w);
        edge_node e;
        e.x = x;
        e.y = y;
        e.w = w;
        edge[i] = e;
    }
    sort(edge.begin(), edge.end());
    int i = 0;
    int j = 0;
    vector<edge_node> result(n - 1);
    A = new subset[n];
    for (int i = 0; i < n; ++i) {
        A[i].parent = i;
        A[i].rank = 0;
    }
    int cost = 0;
    graph *g2 = new graph(n, n - 1);
    while (i < n - 1) {
        edge_node e = edge[j];
        if (find(e.x) != find(e.y)) {
            result[i++] = e;
            Union(e.x, e.y);
            g2->addedge(e.x, e.y, e.w);
            cost += e.w;
        }
        j++;
    }
    int Q;
    int **results = new int *[n];
    for (int i = 0; i < n; ++i) {
        results[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            results[i][j] = -INT_MAX;
        }
    }
    cin >> Q;
    int *a = new int[Q];
    int *b = new int[Q];
    int *done = new int[n];
    for (int i = 0; i < Q; ++i) {
        cin >> x >> y;
        x--;
        y--;
        a[i] = x;
        b[i] = y;
    }
    for (int i = 0; i < n; ++i) {
        done[i] = false;
    }
    for (int i = 0; i < Q; ++i) {
        if (!done[a[i]]) {
            dfs(g2, a[i], results[a[i]]);
            done[a[i]] = true;
        }
        printf("%d\n", results[a[i]][b[i]]);
    }

    return 0;
}