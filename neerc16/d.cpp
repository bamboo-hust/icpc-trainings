#include <bits/stdc++.h>
 
using namespace std;
 
const int INF = 2e9;
 
struct Network {
    struct Edge {
        int v, cap, cost, flow;
        int remain() {
            return cap - flow;
        }
    };
    vector<Edge> E;
    vector< vector<int> > a;
    vector<int> prev;
 
    int n, s, t;
 
    Network(int n, int s, int t): n(n), s(s), t(t) {
        a.resize(n); prev.resize(n);
    }
 
    void add_directed_edge(int u, int v, int cap, int cost) {
        a[u].push_back(E.size()); E.push_back(Edge{v, cap, cost, 0});
        a[v].push_back(E.size()); E.push_back(Edge{u, 0, -cost, 0});
    }
 
    void add_undirected_edge(int u, int v, int cap, int cost) {
        add_directed_edge(u, v, cap, cost);
        add_directed_edge(v, u, cap, cost);
    }
 
    bool find_path() {
        vector<int64_t> d(n, 1LL * INF * INF);
        prev.assign(n, -1);
        queue<int> Q;
        vector<bool> in_queue(n);
        Q.push(s); in_queue[s] = true; d[s] = 0;
        while (!Q.empty()) {
            int u = Q.front(); Q.pop(); in_queue[u] = false;
            for (int e : a[u]) {
                int v = E[e].v;
                if (E[e].flow < E[e].cap && d[v] > d[u] + E[e].cost) {
                    d[v] = d[u] + E[e].cost;
                    prev[v] = e;
                    if (!in_queue[v]) {
                        in_queue[v] = true;
                        Q.push(v);
                    }
                }
            }
        }
        return prev[t] != -1;
    }
 
    pair<int, int64_t> min_cost_max_flow(int limit) {
        int maxflow = 0;
        int64_t mincost = 0;
 
        auto inc_flow = [&]() {
            int flow = INF;
            for (int u = t; u != s; ) {
                int e = prev[u];
                flow = min(flow, E[e].remain());
                u = E[e ^ 1].v;
            }
            for (int u = t; u != s; ) {
                int e = prev[u];
                mincost += 1LL * E[e].cost * flow;
                E[e].flow += flow;
                E[e ^ 1].flow -= flow;
                u = E[e ^ 1].v;
            }
            maxflow += flow;
        };
 
        while (maxflow < limit && find_path()) inc_flow();
        assert(maxflow == limit);
        return make_pair(maxflow, mincost);
    }
};
 
int main() {
    ios::sync_with_stdio(false);
    freopen("delight.in", "r", stdin);
    freopen("delight.out", "w", stdout);
    
    int n, k, ms, me;
    cin >> n >> k >> ms >> me;
    vector<int> cs(n), ce(n);
    for (int i = 0; i < n; ++i) cin >> cs[i];
    for (int i = 0; i < n; ++i) cin >> ce[i];
 
    Network G(n + 2, n, n + 1);
    for (int i = 0; i < k; ++i) {
        G.add_directed_edge(n, i, 1, 0);
    }
    vector<int> edge_id(n);
    for (int i = 0; i < n; ++i) {
        G.add_directed_edge(i, i + 1 < n ? (i + 1) : (n + 1), k - ms - me, 0);
        edge_id[i] = G.E.size();
        G.add_directed_edge(i, i + k < n ? (i + k) : (n + 1), 1, cs[i] - ce[i]);
    }
 
    pair<int, int64_t> foo = G.min_cost_max_flow(k - ms);
    int64_t res = -foo.second;
    for (int i = 0; i < n; ++i) res += cs[i];
    cout << res << endl;
    for (int i = 0; i < n; ++i) {
        cout << (G.E[edge_id[i]].flow ? 'E' : 'S');
    }
    cout << endl;
}