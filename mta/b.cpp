#include <bits/stdc++.h>

using namespace std;

int const N = 1e3 + 5;
long long const MAX = 1e17;

long long dp[N][N], a[N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                dp[i][j] = -MAX;
            }
        }
        dp[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            dp[i][0] = 0;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                long long pos = (j % 5) ? (j % 5) : 5;
                if (pos % 2 == 0) {
                    pos = -pos;
                }
                long long cost = pos * a[i];
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] + cost);
            }
        }

        cout << dp[n][5 * k] << "\n";
    }
}