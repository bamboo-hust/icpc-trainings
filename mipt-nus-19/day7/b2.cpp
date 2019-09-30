#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int INF = 1e9 + 9;

template<class K> class Treap {
    struct Node {
        K key;
        uint32_t prior;
        int size;
        Node *l, *r;
        Node(K key): key(key), prior(rand()), size(1), l(nullptr), r(nullptr) {}
        ~Node() { delete l; delete r; }
    };

    inline int size(Node *x) { return x ? x->size : 0; }

    inline void update(Node *x) {
        if (x) {
            x->size = size(x->l) + size(x->r) + 1;
        }
    }

    void join(Node *&t, Node *l, Node *r) {
        if (!l || !r)
            t = l ? l : r;
        else if (l->prior < r->prior)
            join(l->r, l->r, r), t = l;
        else
            join(r->l, l, r->l), t = r;
        update(t);
    }

    void splitByKey(Node *v, K x, Node* &l, Node* &r) {
        if (!v) return void(l = r = nullptr);
        if (v->key < x)
            splitByKey(v->r, x, v->r, r), l = v;
        else
            splitByKey(v->l, x, l, v->l), r = v;
        update(v);
    }

    void show(Node *x) {
        if (!x) return;
        show(x->l);
        cerr << x->key << ' ';
        show(x->r);
    }

    Node *root;
    Node *l, *m, *r;

public:
    Treap() { root = NULL; }
    ~Treap() { delete root; }
    int size() { return size(root); }

    void clear() {
        delete root;
        root = NULL;
    }

    void insert(K x) {
        splitByKey(root, x, l, r);
        m = new Node(x);
        join(l, l, m);
        join(root, l, r);
    }

    int count_larger(K x) {
        splitByKey(root, x, l, r);
        int res = size(r);
        join(root, l, r);
        return res;
    }

    void show() {
        cerr << "Size = " << size() << " ";
        cerr << "[";
        show(root);
        cerr << "]\n";
    }
};



vector< pair<int, int> > a[N];
bool has_shop[N];
pair<int, int> d[N];
int sz[N];
int res[N];

int n;

bool erased[N];

void dijkstra(pair<int, int> d[N]) {
    set< pair< pair<int, int>, int> > S;
    for (int i = 1; i <= n; ++i) d[i] = {INF, INF};
    for (int i = 1; i <= n; ++i) {
        if (has_shop[i]) {
            d[i] = {0, i};
            S.insert(make_pair(d[i], i));
        }
    }
    while (!S.empty()) {
        int u = S.begin()->second;
        S.erase(S.begin());
        for (auto e : a[u]) {
            int v = e.first;
            int w = e.second;
            pair<int, int> foo = d[u];
            foo.first += w;
            if (d[v] > foo) {
                if (d[v].first != INF) {
                    S.erase(make_pair(d[v], v));
                }
                d[v] = foo;
                S.insert(make_pair(d[v], v));
            }
        }
    }
}

void reset() {
    for (int i = 1; i <= n; ++i) {
        a[i].clear();
        d[i] = {0, 0};
        erased[i] = false;
        sz[i] = 0;
        res[i] = 0;
    }
}

void dfs_size(int u, int p) {
    sz[u] = 1;
    for (auto e : a[u]) {
        int v = e.first;
        if (erased[v]) continue;
        if (v == p) continue;
        dfs_size(v, u);
        sz[u] += sz[v];
    }
}

int dfs_find_centroid(int u, int p, int total) {
    int max_size = 0;
    int to = 0;
    for (auto e : a[u]) {
        int v = e.first;
        if (erased[v]) continue;
        if (v == p) continue;
        if (max_size < sz[v]) {
            max_size = sz[v];
            to = v;
        }
    }
    if (max_size <= total / 2) {
        return u;
    }
    return dfs_find_centroid(to, u, total);
}

int find_centroid(int u) {
    dfs_size(u, 0);
    return dfs_find_centroid(u, 0, sz[u]);
}

void dfs_calc(Treap< pair<int, int> > &T, int u, int p, int sum_w) {
    res[u] += T.count_larger(make_pair(sum_w, u));
    for (auto e : a[u]) {
        int v = e.first;
        int w = e.second;
        if (erased[v]) continue;
        if (v == p) continue;
        dfs_calc(T, v, u, sum_w + w);
    }
}

void dfs_update(Treap< pair<int, int> > &T, int u, int p, int sum_w) {
    T.insert(make_pair(d[u].first - sum_w, d[u].second));
    for (auto e : a[u]) {
        int v = e.first;
        int w = e.second;
        if (erased[v]) continue;
        if (v == p) continue;
        dfs_update(T, v, u, sum_w + w);
    }
}

void dfs_for_centroid(int root, int u, int p, int sum_w) {
    res[u] += d[root] > make_pair(sum_w, u);
    if (root != u) res[root] += d[u] > make_pair(sum_w, root);
    for (auto e : a[u]) {
        int v = e.first;
        int w = e.second;
        if (erased[v]) continue;
        if (v == p) continue;
        dfs_for_centroid(root, v, u, sum_w + w);
    }
}

void dfs_solve(int u) {
    int centroid = find_centroid(u);
    dfs_for_centroid(centroid, centroid, 0, 0);
    Treap< pair<int, int> >T;
    for (int i = 0; i < a[centroid].size(); ++i) {
        int v = a[centroid][i].first;
        int w = a[centroid][i].second;
        if (erased[v]) continue;
        dfs_calc(T, v, centroid, w);
        dfs_update(T, v, centroid, w);
    }
    T.clear();
    for (int i = (int) a[centroid].size() - 1; i >= 0; --i) {
        int v = a[centroid][i].first;
        int w = a[centroid][i].second;
        if (erased[v]) continue;
        dfs_calc(T, v, centroid, w);
        dfs_update(T, v, centroid, w);
    }
    erased[centroid] = true;
    for (auto e : a[centroid]) {
        int v = e.first;
        if (erased[v]) continue;
        dfs_solve(v);
    }
}

void read() {
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        a[u].push_back(make_pair(v, w));
        a[v].push_back(make_pair(u, w));
    }
    for (int i = 1; i <= n; ++i) cin >> has_shop[i];
}

int main() {
    ios::sync_with_stdio(false);

    while (cin >> n) {
        read();
        dijkstra(d);
        dfs_solve(1);

        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            ans = max(ans, res[i]);
        }
        cout << ans << '\n';
        reset();
    }
}
