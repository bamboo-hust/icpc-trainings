#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007;
const int N = 100010;
const int B = 100;

inline int add(int u, int v) {
    return (u += v) >= MOD ? u - MOD : u;
}

inline int sub(int u, int v) {
    return (u -= v) < 0 ? u + MOD : u;
}

inline int mul(int u, int v) {
    return (long long)u * v % MOD;
}

inline int power(int u, int v) {
    int res = 1;
    while (v) {
        if (v & 1) res = mul(res, u);
        u = mul(u, u);
        v >>= 1;
    }
    return res;
}

int n, m, c;
vector<int> adj[N];
int deg[N];
int f[2][N];

int dp[2][B][B];
int lv[B];
vector<int> bigAdj[B];
int isGood[B];
bool used[B];
vector<int> colors;
map<pair<vector<int>, pair<int, int>>, int> cache;

pair<int, int> go(int u, int v) {
    int cnt = 0;
    while (deg[v] == 2) {
        cnt++;
        vector<int> ls;
        for (int w : adj[v]) {
            if (deg[w] < 2) continue;
            ls.push_back(w);
        }
        assert(ls.size() == 2);
        if (ls[0] == u) swap(ls[0], ls[1]);
        u = v;
        v = ls[0];
    }
    return {v, cnt};
}

void dfsInit(int u) {
    used[u] = 1;
    for (int v : bigAdj[u]) {
        if (used[v]) {
            if (lv[v] + 1 < lv[u]) isGood[v] = 1;
        } else {
            lv[v] = lv[u] + 1;
            dfsInit(v);
        }
    }
}

int dfs(int u, int colorOfPar) {
    if (cache.count({colors, {u, colorOfPar}})) return cache[{colors, {u, colorOfPar}}];
    int res = 0;
    int maxColor = *max_element(colors.begin(), colors.end());
    for (int i = 1; i <= maxColor; i++) {
        int now = 1;
        for (int v : bigAdj[u]) {
            assert(lv[v] != lv[u]);
            if (lv[v] > lv[u]) continue;
            if (lv[v] + 1 == lv[u]) {
                now = mul(now, dp[colorOfPar != i][u][v]);
            }
            if (lv[v] + 1 < lv[u]) {
                now = mul(now, dp[colors[v] != i][u][v]);
            }
        }

        if (now == 0) continue;

        if (isGood[u]) colors[u] = i;
        else colors[u] = 0;
        for (int v : bigAdj[u]) {
            if (lv[v] != lv[u] + 1) continue;
            now = mul(now, dfs(v, i));
        }
        colors[u] = 0;

        res = add(res, now);
    }
    if (colorOfPar > maxColor) {
        int equalsToPar = 1;
        int diffToPar = c - maxColor - 1;
        for (int v : bigAdj[u]) {
            assert(lv[v] != lv[u]);
            if (lv[v] > lv[u]) continue;
            if (lv[v] + 1 == lv[u]) {
                equalsToPar = mul(equalsToPar, dp[0][u][v]);
                diffToPar = mul(diffToPar, dp[1][u][v]);
            }
            if (lv[v] + 1 < lv[u]) {
                equalsToPar = mul(equalsToPar, dp[1][u][v]);
                diffToPar = mul(diffToPar, dp[1][u][v]);
            }
        }
        int now = add(equalsToPar, diffToPar);
        if (now > 0) {
            if (isGood[u]) colors[u] = maxColor + 1;
            else colors[u] = 0;
            for (int v : bigAdj[u]) {
                if (lv[v] != lv[u] + 1) continue;
                now = mul(now, dfs(v, maxColor + 1));
            }
            colors[u] = 0;

            res = add(res, now);
        }
    } else {
        int now = c - maxColor;
        for (int v : bigAdj[u]) {
            assert(lv[v] != lv[u]);
            if (lv[v] > lv[u]) continue;
            if (lv[v] + 1 == lv[u]) {
                now = mul(now, dp[1][u][v]);
            }
            if (lv[v] + 1 < lv[u]) {
                now = mul(now, dp[1][u][v]);
            }
        }
        if (now > 0) {
            if (isGood[u]) colors[u] = maxColor + 1;
            else colors[u] = 0;
            for (int v : bigAdj[u]) {
                if (lv[v] != lv[u] + 1) continue;
                now = mul(now, dfs(v, maxColor + 1));
            }
            colors[u] = 0;

            res = add(res, now);
        }
    }
    cache[{colors, {u, colorOfPar}}] = res;
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> c;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++, deg[v]++;
    }
    if (c == 1) {
        if (m == 0) cout << 1 << endl;
        else cout << 0 << endl;
        return 0;
    }
    if (m == n - 1) {
        cout << mul(c, power(c - 1, n - 1)) << endl;
        return 0;
    }
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1) q.push(i);
    }
    int res = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        res = mul(res, c - 1);
        for (int v : adj[u]) {
            deg[v]--;
            if (deg[v] == 1) {
                q.push(v);
            }
        }
    }   
    
    f[0][0] = 0;
    f[0][1] = c - 1;
    f[1][0] = 1;
    f[1][1] = c - 2;

    for (int i = 2; i < N; i++) {
        f[0][i] = add(mul(f[0][i - 2], f[0][1]), mul(mul(f[1][i - 2], f[1][1]), c - 1));
        f[1][i] = add(mul(f[0][i - 2], f[1][1]), mul(f[1][i - 2], f[0][1]));
        f[1][i] = add(f[1][i], mul(mul(f[1][i - 2], f[1][1]), c - 2));
    }

    int num = 0;    
    vector<int> bigVertices;
    for (int i = 1; i <= n; i++) {
        if (deg[i] >= 3) bigVertices.push_back(i);
        num += deg[i] >= 2;
    }
    if (bigVertices.empty()) {
        res = mul(res, c);
        res = mul(res, f[0][num - 1]);
        cout << res << endl;
        return 0;
    }
    sort(bigVertices.begin(), bigVertices.end());
    for (int i = 0; i < bigVertices.size(); i++) {
        for (int j = 0; j < bigVertices.size(); j++) {
            dp[0][i][j] = dp[1][i][j] = 1;
        }
    }
    for (int i = 0; i < bigVertices.size(); i++) {
        int u = bigVertices[i];
        vector<int> toSelf;
        for (int v : adj[u]) {
            if (deg[v] >= 2) {
                pair<int, int> foo = go(u, v);
                if (foo.first == u) {
                    toSelf.push_back(foo.second);
                    continue;
                }
                int id = lower_bound(bigVertices.begin(), bigVertices.end(), foo.first) - bigVertices.begin();
                dp[0][i][id] = mul(dp[0][i][id], f[0][foo.second]);
                dp[1][i][id] = mul(dp[1][i][id], f[1][foo.second]);
                bigAdj[i].push_back(id);
            }   
        }
        sort(toSelf.begin(), toSelf.end());
        for (int j = 0; j < toSelf.size(); j += 2) {
            res = mul(res, f[0][toSelf[j]]);
        }
    }
    for (int i = 0; i < bigVertices.size(); i++) {
        sort(bigAdj[i].begin(), bigAdj[i].end());
        bigAdj[i].resize(unique(bigAdj[i].begin(), bigAdj[i].end()) - bigAdj[i].begin());
    }

    colors.resize(bigVertices.size(), 0);
    dfsInit(0);
    int now = dfs(0, 0);
    res = mul(res, now);
    cout << res << endl;
    return 0;   
}