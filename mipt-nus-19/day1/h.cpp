#include <bits/stdc++.h>

using namespace std;

const int N = 128;
const int T = N * 2 + N * N * 2;
const int INF = 1e9;
const int LIM = 1000006;

int d[N][N];
int total;
int n;
int open[N], close[N], speed[N];
int f[T][N];

vector<int> V;

int nxt[LIM];

void maximize(int &a, int b) {
    if (b >= total) b = total;
    if (a < b) a = b;
}

int get_next(int t) {
    if (t >= LIM) return V.size();
    if (nxt[t] != -1) return nxt[t];
    return nxt[t] = lower_bound(begin(V), end(V), t) - V.begin();
}

int get_data(int t, int i) {
    if (open[i] <= V[t] && V[t + 1] <= close[i]) return min(1LL * speed[i] * (V[t + 1] - V[t]), 1LL * total);
    return 0;
}

int main() {
    cin >> total;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> open[i] >> close[i] >> speed[i];
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            d[i][j] = i == j ? 0 : INF;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> d[i][j];
        }
    }
    for (int k = 1; k <= n; ++k) {
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                d[u][v] = min(d[u][v], d[u][k] + d[k][v]);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        V.push_back(open[i]);
        V.push_back(close[i]);
        for (int j = 1; j <= n; ++j) {
            V.push_back(open[i] - d[j][i]);
            V.push_back(close[i] + d[i][j]);
        }
    }
    V.push_back(INF);
    memset(nxt, -1, sizeof nxt);
    sort(begin(V), end(V));
    V.resize(unique(begin(V), end(V)) - begin(V));
    int res = INF;
    memset(f, -1, sizeof f);
    for (int i = 1; i <= n; ++i) {
        f[lower_bound(begin(V), end(V), open[i]) - V.begin()][i] = 0;
    }
    for (int t = 0; t < V.size(); ++t) for (int i = 1; i <= n; ++i) if (f[t][i] != -1) {
        //cerr << "dp " << V[t] << ' ' << i << ' ' << f[t][i] << endl;
        for (int j = 1; j <= n; ++j) {
            int tt = get_next(V[t] + d[i][j]);
            if (tt < V.size()) maximize(f[tt][j], f[t][i]);
        }
        if (t + 1 < V.size()) maximize(f[t + 1][i], f[t][i] + get_data(t, i));
        if (t + 1 < V.size() && f[t][i] + get_data(t, i) >= total) {
            int remain = total - f[t][i];
            if (remain <= 0) {
                res = min(res, V[t]);
            } else if (open[i] <= V[t] && V[t + 1] <= close[i]) {
                int take = remain / speed[i];
                if (remain % speed[i]) take++;
                res = min(res, V[t] + take);
            }
        }
    }

    cout << res << endl;
}