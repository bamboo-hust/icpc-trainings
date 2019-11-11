#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int a[N];
int64_t dp[N];
int n;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        int64_t res = 0;
        for (int i = 1; i <= n; ++i) if (a[i] != 0) {
            dp[i] = dp[i - 1];
            dp[i] = max(dp[i], (i >= 2 ? dp[i - 2] : 0) + a[i]);
            if (i >= 3) {
                dp[i] = max(dp[i], dp[i - 3] + a[i] + min(a[i - 1], a[i - 2]));
            }
            res = max(res, dp[i]);
        }
        cout << res << '\n';
    }
}