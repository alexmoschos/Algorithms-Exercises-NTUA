#include <iostream>
#include <limits.h>
#include <queue>
#include <vector>
#define min(a, b) ((a) > (b) ? (b) : (a))

using namespace std;

typedef pair<int, int> intpair;
struct node_t {
    int id;
    int weight;
};
typedef struct node_t *node;
struct heap_t {
    int size;
    int capacity;
    int *position;
    node *array;
};
typedef struct heap_t *minheap;
minheap createminheap(int n) {
    minheap heap = new struct heap_t;

    heap->position = new int[n];
    heap->size = 0;
    heap->capacity = n;
    heap->array = new node[n];
    return heap;
}
void swap(node &a, node &b) {
    node t = a;
    a = b;
    b = t;
}

void Heapify(minheap heap, int x) {
    int lch, rch, s;
    s = x;
    lch = 2 * x + 1;
    rch = 2 * x + 2;
    if (lch < heap->size && heap->array[lch]->weight < heap->array[s]->weight)
        s = lch;
    if (rch < heap->size && heap->array[rch]->weight < heap->array[s]->weight)
        s = rch;
    if (s != x) {
        heap->position[heap->array[s]->id] = x;
        heap->position[heap->array[x]->id] = s;
        swap(heap->array[s], heap->array[x]);
        Heapify(heap, s);
    }
}

node extractMin(minheap heap) {
    if (heap->size == 0)
        return NULL;
    node root = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->position[heap->array[0]->id] = 0;
    heap->position[root->id] = heap->size - 1;
    heap->size--;
    Heapify(heap, 0);
    return root;
}

void decreaseKey(minheap heap, int v, int key) {
    int i = heap->position[v];
    heap->array[i]->weight = key;
    while (i > 0 && heap->array[i]->weight < heap->array[(i - 1) / 2]->weight) {
        heap->position[heap->array[i]->id] = (i - 1) / 2;
        heap->position[heap->array[(i - 1) / 2]->id] = i;
        swap(heap->array[i], heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

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
    ~graph();
    void addedge(int u, int v, int w) {
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
};

int prim(graph *g) {
    int n = g->n;
    n--;
    int *key = new int[n];
    bool *visited = new bool[n];
    minheap heap = createminheap(n);
    for (int i = 0; i < n; ++i) {
        key[i] = INT_MAX;
        visited[i] = false;
        node x = new struct node_t;
        x->id = i;
        x->weight = key[i];
        heap->array[i] = x;
        heap->position[i] = i;
    }
    int i = 0;
    int cost = 0;
    key[0] = 0;
    node x = new struct node_t;
    x->id = 0;
    x->weight = 0;
    heap->position[0] = 0;
    heap->array[0] = x;
    heap->size = n;
    while (i < n) {
        node current = extractMin(heap);
        int u = current->id;
        cost += current->weight;
        visited[u] = true;
        for (intpair next : g->adj[u]) {
            int v = next.first;
            int w = next.second;
            if (!visited[v] && w < key[v]) {
                key[v] = w;
                decreaseKey(heap, v, key[v]);
            }
        }
        ++i;
    }
    return cost;
}

int main(int argc, char const *argv[]) {
    int n, m, x, y, w, next, k, j;
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> k >> m;
    graph *g = new graph(n + 1, m);
    int *B = new int[n];
    // cout << k << endl;
    for (int i = 0; i < k; ++i) {
        int r;
        cin >> j >> r;
        j--;
        B[j] = r;
    }
    for (int i = 0; i < m; ++i) {
        cin >> x >> y >> w;
        x--;
        y--;
        g->addedge(x, y, w);
    }

    int cost1 = prim(g);
    for (int i = 0; i < n; ++i) {
        if (B[i] != 0) {
            g->addedge(i, n, B[i]);
        }
    }

    g->n++;
    int cost2 = prim(g);
    // cout << cost2 << endl;
    cout << min(cost2, cost1) << endl;
    return 0;
}