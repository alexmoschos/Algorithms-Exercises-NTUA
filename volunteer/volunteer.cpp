#include <iostream>
#include <limits.h>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;

typedef pair<int, int> intp;
set<intp> se;
int counter;
vector<int> *result;
int *where;
class graph {
  public:
    std::vector<int> *adj;
    int n;
    int m;
    graph(int n, int m) {
        this->n = n;
        this->m = m;
        adj = new vector<int>[n];
    }
    ~graph() {}
    void addedge(int u, int v, int w) {
        adj[u].push_back(v);
        // adj[v].push_back(make_pair(u,w));
    }
};

void dfs(graph g, int start, bool *v, stack<int> &s) {
    v[start] = true;
    for (auto i : g.adj[start]) {
        if (!v[i]) {
            dfs(g, i, v, s);
        }
    }
    s.push(start);
}

void dfsutil(graph g, int start, bool *v) {
    v[start] = true;
    result[counter].push_back(start);
    where[start] = counter;
    // cout << start + 1 << " ";
    for (auto i : g.adj[start]) {
        if (!v[i]) {
            dfsutil(g, i, v);
        }
    }
}

void topological(graph g, int start, bool *v, stack<int> &s) {
    v[start] = true;
    for (auto i : g.adj[start]) {
        if (!v[i])
            topological(g, i, v, s);
    }
    s.push(start);
}

int *longestpath(graph g, int s, int *label) {
    stack<int> stack;
    int *dist = new int[g.n];
    bool *visited = new bool[g.n];
    for (int i = 0; i < counter; ++i) {
        visited[i] = false;
    }
    for (int i = 0; i < counter; ++i) {
        if (visited[i] == false)
            topological(g, i, visited, stack);
    }
    for (int i = 0; i < counter; ++i) {
        dist[i] = -INT_MAX;
    }
    dist[s] = label[s];
    while (!stack.empty()) {
        int u = stack.top();
        stack.pop();
        if (dist[u] != -INT_MAX) {
            for (auto i : g.adj[u]) {
                if (dist[i] < dist[u] + label[i]) {
                    // cout << "Relax" << endl;
                    // cout << dist[i] << endl;
                    dist[i] = dist[u] + label[i];
                    // cout << dist[i] << endl;
                }
            }
        }
    }
    return dist;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int n, m;
    int x, y;
    cin >> n >> m;
    int *o = new int[n];
    int *f = new int[n];
    graph *g = new graph(n, m);
    graph *g2 = new graph(n, m);
    intp *edges = new intp[m];
    where = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> o[i] >> f[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> x >> y;
        x--;
        y--;
        g->addedge(x, y, 0);
        g2->addedge(y, x, 0);
        edges[i] = make_pair(x, y);
    }
    result = new vector<int>[n];
    stack<int> s;
    bool *visitedset = new bool[n];
    for (int i = 0; i < n; ++i) {
        visitedset[i] = false;
    }
    for (int i = 0; i < n; ++i) {
        if (!visitedset[i])
            dfs(*g, i, visitedset, s);
    }
    for (int i = 0; i < n; ++i) {
        visitedset[i] = false;
    }
    while (!s.empty()) {
        int v = s.top();
        s.pop();
        if (!visitedset[v]) {
            dfsutil(*g2, v, visitedset);
            // cout << endl;
            counter++;
        }
    }

    int *label = new int[counter];
    bool *cond = new bool[counter];
    // cout << endl;
    for (int i = 0; i < counter; ++i) {
        label[i] = 0;
        cond[i] = 0;
        for (auto j : result[i]) {
            label[i] += f[j];
            cond[i] = cond[i] || o[j];
        }
        // cout << i << " ";
        // cout << label[i] << " ";
        // cout << cond[i];
        // cout << endl;
    }
    delete g;
    delete g2;
    graph *dag = new graph(counter, m);
    for (int i = 0; i < m; ++i) {
        x = edges[i].first;
        y = edges[i].second;

        if (where[x] != where[y] &&
            se.find(make_pair(where[x], where[y])) == se.end()) {
            // cout << "Edge" << where[x] << " " << where[y] << endl;
            dag->addedge(where[x], where[y], 0);
            se.insert(make_pair(where[x], where[y]));
            se.insert(make_pair(where[y], where[x]));
        }
    }
    // int* d = longestpath(*dag,where[0],label);
    int *dist = f;
    int start = where[0];
    for (int i = 0; i < counter; ++i) {
        dist[i] = -INT_MAX;
    }
    dist[start] = label[start];
    for (int i = 0; i < counter; ++i) {
        int u = i;
        // stack.pop();
        if (dist[u] != -INT_MAX) {
            for (auto i : dag->adj[u]) {
                if (dist[i] < dist[u] + label[i]) {
                    dist[i] = dist[u] + label[i];
                }
            }
        }
    }
    int *d = dist;
    int max = -INT_MAX;
    for (int i = 0; i < counter; ++i) {
        if (cond[i]) {
            if (d[i] > max) {
                max = d[i];
            }
        }
    }
    // cout << counter << endl;
    cout << ((max >= 0) ? max : -1) << endl;
    return 0;
}