#include <bits/stdc++.h>

using namespace std;

const int N = 1e5;

struct Flow {
    static const int V = 1000000;
    int head[V], to[V], c[V], cost[V], f[V], nxt[V], h[V], par[V], inQueue[V];
    int s, t, n, cnt;
    queue <int> q;
    Flow (int n, int s, int t) {
        this->n = n;
        this->s = s;
        this->t = t;
        cnt = 0;
        for (int i=  0; i < n; i++) {
            head[i] = -1;
            inQueue[i] = 0;
        }
    }
    int addEdge(int u, int v, int _c, int _cost) {
        to[cnt] = v, c[cnt] = _c, cost[cnt] = _cost, f[cnt] = 0, nxt[cnt] = head[u], head[u] = cnt++;
        to[cnt] = u, c[cnt] = 0, cost[cnt] = -_cost, f[cnt] = 0, nxt[cnt] = head[v], head[v] = cnt++;
        return cnt - 2;
    }
    pair<int, int> maxFlow () {
        int res = 0, minCost = 0;
        while (1) {
            for (int i = 0; i < n; i++) {
                par[i] = -1;
                h[i] = 2e9;
            }
            h[s] = 0;
            q.push(s);
            inQueue[s] = 1;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                inQueue[u] = 0;
                for (int id = head[u]; id != -1; id = nxt[id]) {
                    int v = to[id];
                    if (h[v] > h[u] + cost[id] && f[id] < c[id]) {
                        h[v] = h[u] + cost[id];
                        par[v] = id;
                        if (!inQueue[v]) {
                            inQueue[v] = 1;
                            q.push(v);
                        }
                    }
                }
            }
            if (par[t] == -1) {
                break;
            }
            int x = t;
            int now = 2e9;
            while (x != s) {
                int id = par[x];
                now = min(now, c[id] - f[id]);
                x = to[id ^ 1];
            }
            x = t;
            while (x != s) {
                int id = par[x];
                minCost += cost[id] * now;
                f[id] += now;
                f[id ^ 1] -= now;
                x = to[id ^ 1];
            }
            res += now;
        }
        return make_pair(res, minCost);
    }
};

int getVal(int x, int y, int u, int v) {
    return abs(x - u) + abs(y - v);
}

int main() {
    int n;
    cin >> n;
    Flow f(n * 2 + 2, 0, n * 2 + 1);
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        for (int j = 1; j <= n; j++) {
            f.addEdge(i, j + n, 1, getVal(x, y, j, j));
        }
    }
    for (int i = 1; i <= n; i++) {
        f.addEdge(f.s, i, 1, 0);
        f.addEdge(i + n, f.t, 1, 0);
    }
    pair<int, int> res = f.maxFlow();
    cout << res.second << endl;
    return 0;
}