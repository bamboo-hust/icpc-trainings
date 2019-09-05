#include <bits/stdc++.h>

using namespace std;
#define f first
#define s second;


int const N = 2e5 + 5;
int const NN = 18;

struct Edge
{
    int u, v, w;
    Edge(){};
    Edge(int _u, int _v, int _w) {
        u = _u;
        v = _v;
        w = _w;
    }
};

Edge e[N];

struct Query
{
    int u, v, pos, id, mid, p;
    Query(){};
    Query(int _u, int _v, int _pos, int _id, int _p) {
        u = _u;
        v = _v;
        pos = _pos;
        id = _id;
        p = _p;
    }
};
Query que[N];

struct BIT
{
    int tree[N];
    void reset() {
        memset(tree, 0, sizeof(tree));
    }
    void update(int x, int val) {
        while (x < N) {
            tree[x] += val;
            x += x & (-x);
        }
    }

    int get(int x) {
        int res = 0;
        while (x) {
            res += tree[x];
            x -= x & (-x);
        }
        return res;
    }
};

BIT T;


int in[N], out[N], h[N], par[NN][N], tot, l[N], r[N];

vector < pair < int, int > > a[N];

void dfs(int u, int pre) {
    in[u] = ++tot;
    for (int i = 0; i < a[u].size(); i++) {
        int v = a[u][i].f;
        int w = a[u][i].s;
        if (v == pre) {
            continue;
        }
        h[v] = h[u] + 1;
        par[0][v] = u;
        dfs(v, u);
    }
    out[u] = tot;
}

int get_lca(int u, int v) {
    if (h[u] < h[v]) {
        swap(u, v);
    }
    int diff = h[u] - h[v];
    for (int j = 0; j < NN; j++) {
        if ((diff >> j) & 1) {
            u = par[j][u];
        }
    }
    if (u == v) {
        return u;
    }
    for (int j = NN - 1; j >= 0; j--) {
        if (par[j][u] != par[j][v]) {
            u = par[j][u];
            v = par[j][v];
        }
    }
    return par[0][u];
}

bool cmp_que(Query p, Query q) {
    return p.mid < q.mid;
}

bool cmp_edge(Edge p, Edge q) {
    return p.w < q.w;
}


void push_edge(int u, int v) {
    if (h[u] < h[v]) {
        swap(u, v);
    }
    T.update(in[u], 1);
    T.update(out[u] + 1, -1);
    //cout << "update : " << in[u] << " " << out[u] << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    int test_case;
    cin >> test_case;
    while (test_case--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            a[i].clear();
        }
        for (int i = 1; i < n; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            e[i] = Edge(u, v, w);
            a[u].push_back(make_pair(v, w));
            a[v].push_back(make_pair(u, w));
        }
        sort(e + 1, e + n, cmp_edge);
        dfs(1, 0);
        for (int j = 1; j < NN; j++) {
            for (int i = 1; i <= n; i++) {
                par[j][i] = par[j - 1][par[j - 1][i]];
            }
        }
        int q, cnt = 0;
        cin >> q;
        for (int i = 1; i <= q; i++) {
            int u, v;
            cin >> u >> v;
            int p = get_lca(u, v);
            int length = h[u] + h[v] - h[p] * 2;
            if (length % 2 == 0) {
                que[++cnt] = Query(u, v, length / 2, i * 2 - 1, p);
                que[++cnt] = Query(u, v, length / 2 + 1, i * 2, p);
            } else {
                que[++cnt] = Query(u, v, length / 2 + 1, i * 2 - 1, p);
                que[++cnt] = Query(u, v, length / 2 + 1, i * 2, p);
            }
        }

        q = cnt;
        for (int i = 1; i <= q; i++) {
            l[i] = 0;
            r[i] = N + 1;
        }
        int step = NN;
        while (step--) {
            for (int i = 1; i <= q; i++) {
                int id = que[i].id;
                que[i].mid = (l[id] + r[id]) / 2;
            }
            sort (que + 1, que + q + 1, cmp_que);
            int pos = 1;
            for (int i = 1; i <= q; i++) {
                int id = que[i].id;
                while (e[pos].w <= que[i].mid && pos < n) {
                    push_edge(e[pos].u, e[pos].v);
                    pos++;
                }
                int sum = T.get(in[que[i].u]) + T.get(in[que[i].v]) - T.get(in[que[i].p]) * 2;
                /*if (id == 1) {
                    cout << "sum : " << sum << endl;
                    cout << "pos : " << in[que[i].u] << " " << in[que[i].v] << " " << in[que[i].p] << endl;
                    cout << "val : " << T.get(in[que[i].u]) << " " << T.get(in[que[i].v]) << " " << T.get(in[que[i].p]) << endl;
                }*/
                if (sum >= que[i].pos) {
                    r[id] = que[i].mid;
                } else {
                    l[id] = que[i].mid;
                }
            }
            T.reset();
        }

        for (int i = 1; i <= q / 2; i++) {
            int sum = r[i * 2 - 1] + r[i * 2];
            cout << sum / 2 << ".";
            if (sum % 2 == 0) {
                cout << "0" << endl;
            } else {
                cout << "5" << endl;
            }
        }
    }
}