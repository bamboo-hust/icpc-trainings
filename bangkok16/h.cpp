#include <bits/stdc++.h>

using namespace std;

const int V = 105;
const int N = 8;

int K, M;
int n;
int E[N];
int P[N];

int dp[1 << N][2][V][V];

void maximize(int &a, int b) {
    if (a < b) a = b;
}

int solve() {
    memset(dp, -1, sizeof dp);
    dp[0][0][100][0] = 0;
    int res = 0;
    for (int mask = 0; mask < (1 << n); ++mask)  for (int j = 0; j <= 1; ++j) {
        for (int e = 100; e > 0; --e) {
            for (int p = 0; p < 100; ++p) if (~dp[mask][j][e][p]) {
            
                //for (int bit = 0; bit < n; ++bit) cerr << (mask >> bit & 1); cerr << j << ' ' << e << ' ' << p << ' ' << dp[mask][j][e][p] << endl;

                maximize(res, dp[mask][j][e][p]);
                // no potion
                if (e > K) {
                    maximize(dp[mask][1][e - K][max(0, p - M)], dp[mask][j][e][p] + 1);
                }
                if (j) for (int i = 0; i < n; ++i) if (!(mask & (1 << i))) {
                    if (p + P[i] < 100) {
                        maximize(dp[mask | (1 << i)][0][min(100, e + E[i])][p + P[i]], dp[mask][j][e][p]);
                    }
                }
            }
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        cin >> K >> M;
        cin >> n;
        for (int i = 0; i < n; ++i) cin >> E[i];
        for (int i = 0; i < n; ++i) cin >> P[i];
        cout << solve() << '\n';
    }
}