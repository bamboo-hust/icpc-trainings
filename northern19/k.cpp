#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int to;
    int cost;
    int id;

    bool operator < (const Edge &o) const {
        if (to != o.to) return to < o.to;
        return cost > o.cost;
    }
};

const int N = 2019;

int64_t dp[N][N]; // dp[i][j] = max_cost, current pos is i, a guy is using j-th Edge
Edge E[N];
vector<Edge> a[N];
int n, m;

void maximize(int64_t &a, int64_t b) {
    if (a < b) a = b;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= m; ++i) {
            int u, v, c;
            cin >> u >> v >> c;
            E[i] = {v, c, i};
            a[u].push_back(E[i]);
        }
        for (int i = 1; i <= n; ++i) {
            sort(a[i].begin(), a[i].end());
        }
        for (int i = 0; i <= n + 1; ++i) for (int j = 0; j <= m; ++j) dp[i][j] = -1;
        dp[1][0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) if (dp[i][j] >= 0) {
                //cerr << i << ' ' << j << ' ' << dp[i][j] << endl;
                if (E[j].to > i) {
                    maximize(dp[i + 1][j], dp[i][j]);
                }
                if (E[j].to == i) {
                    maximize(dp[i][0], dp[i][j] + E[j].cost);
                } else {
                    for (int k = 0; k < a[i].size(); ++k) {
                        Edge e1 = a[i][k];
                        Edge e2 = E[j];
                        if (e1.to > e2.to) swap(e1, e2);
                        if (e1.to != e2.to) {
                            maximize(dp[e1.to][e2.id], dp[i][j] + e1.cost);
                        } else {
                            maximize(dp[e1.to][0], dp[i][j] + e1.cost + e2.cost);
                        }
                    }
                }
            }
            maximize(dp[i + 1][0], dp[i][0]);
            for (int k = 0; k < a[i].size(); ++k) {
                Edge e = a[i][k];
                maximize(dp[i + 1][e.id], dp[i][0]);
            }
            for (int j = 0; j < a[i].size(); ++j) {
                for (int k = j + 1; k < a[i].size(); ++k) {
                    Edge e1 = a[i][j];
                    Edge e2 = a[i][k];
                    if (e1.to != e2.to) {
                        maximize(dp[e1.to][e2.id], dp[i][0] + e1.cost);
                    } else {
                        maximize(dp[e1.to][0], dp[i][0] + e1.cost + e2.cost);
                    }
                }
            }
        }

        cout << dp[n][0] << '\n';
        for (int i = 1; i <= n; ++i) a[i].clear();
        
    }
}