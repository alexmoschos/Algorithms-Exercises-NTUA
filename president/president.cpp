#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;

typedef pair<int, int> intp;
set<intp> s;
class graph {
  public:
    std::vector<pair<int, int>> *adj;
    int n;
    int m;
    graph(int n, int m) {
        this->n = n;
        this->m = m;
        adj = new vector<pair<int, int>>[n];
    }
    ~graph() {}
    void addedge(int u, int v, int w) {
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
};
int findedgeweight(graph g, int u, int v) {
    s.insert(make_pair(u, v));
    s.insert(make_pair(v, u));

    for (auto i : g.adj[u]) {
        if (i.first == v) {
            return i.second;
        }
    }
    return -1;
}

void dijkstra(graph g, int start, int end, vector<int> &d, vector<int> &p,
              int time, int *ps) {
    priority_queue<intp, vector<intp>, greater<intp>> pq;
    pq.push(make_pair(0, start));
    d[start] = time;
    while (!pq.empty()) {
        int current = pq.top().second;
        // cout << "current: " << current << " d: " << d[current] << endl;
        pq.pop();
        if (current == end) {
            break;
        }
        for (auto i : g.adj[current]) {
            int v = (i).first;
            int weight = (i).second;
            int newcost = weight + d[current];
            if (s.find(make_pair(current, v)) != s.end()) {
                // president visits this edge
                int small = min(ps[current], ps[v]);
                int big = max(ps[current], ps[v]);
                if (d[current] > small && d[current] < big) {
                    newcost = big + weight;
                }
                if (newcost == big && d[current] == small) {
                    newcost = big + weight;
                }
            }
            if (newcost < d[v]) {
                //	cout << "Relaxed " << v  << "d " << weight << endl;
                d[v] = newcost;
                p[v] = current;
                pq.push(make_pair(d[v], v));
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);

    int n, m, start, goal, time, k;
    int x, y, w;
    int *c;
    int *ps;
    int *pe;
    cin >> n >> m;
    cin >> start >> goal >> time >> k;
    start--;
    goal--;
    vector<int> d(n, 100000000);

    vector<int> p(n, -1);
    c = new int[k];
    ps = new int[n];
    int j = 0;
    for (int i = 0; i < k; ++i) {
        cin >> j;
        j--;
        c[i] = j;
    }
    graph *g = new graph(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> x >> y >> w;
        x--;
        y--;
        g->addedge(x, y, w);
    }
    j = 0;
    for (int i = 0; i < n; ++i) {
        ps[i] = -1;
    }
    ps[c[0]] = 0;
    for (int i = 1; i < k; ++i) {
        j += findedgeweight(*g, c[i], c[i - 1]);
        ps[c[i]] = j;
    }
    dijkstra(*g, start, goal, d, p, time, ps);

    cout << d[goal] - time << endl;

    return 0;
}