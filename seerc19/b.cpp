#include <bits/stdc++.h>

using namespace std;

const int N = 510;
const long long INF = (1ll << 60);

int n, s1, s2;
int x[N], y[N], t[N], r[N];
long long dp[2][N][N];
int id[N];

int main() {
    cin >> n >> s1 >> s2;
    for (int i = 1; i <= n; i++) id[i] = i;
    for (int i = 1; i <= n; i++) cin >> x[i] >> t[i] >> y[i] >> r[i];
    sort(id + 1, id + n + 1, [&](int u, int v) {
        return x[u] < x[v];
    });
    for (int j = 0; j <= s1; j++) for (int k = 0; k <= s2; k++) dp[0][j][k] = INF;
    dp[0][0][0] = 0;
    int cur = 0;
    for (int i = 0; i < n; i++, cur ^= 1) {
        int now = id[i + 1];
        for (int j = 0; j <= s1; j++) for (int k = 0; k <= s2; k++) dp[cur ^ 1][j][k] = INF;

        for (int j = 0; j <= s1; j++) {
            for (int k = 0; k <= s2; k++) {
                if (dp[cur][j][k] >= INF) continue;
                // do nothing
                dp[cur ^ 1][j][k] = min(dp[cur ^ 1][j][k], dp[cur][j][k]);
                // do type 1
                if (j < s1) {
                    int jj = j + x[now];
                    int kk = k;
                    if (jj > s1) {
                        kk += jj - s1;
                        jj = s1;
                        kk = min(kk, s2);
                    }
                    dp[cur ^ 1][jj][kk] = min(dp[cur ^ 1][jj][kk], dp[cur][j][k] + t[now]);
                }
                // do type 2;
                int kk = min(k + y[now], s2);
                dp[cur ^ 1][j][kk] = min(dp[cur ^ 1][j][kk], dp[cur][j][k] + r[now]);
            }
        }
    }
    if (dp[cur][s1][s2] >= INF) cout << -1 << endl;
    else cout << dp[cur][s1][s2] << endl;
    return 0;
}