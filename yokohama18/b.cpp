#include <bits/stdc++.h>

using namespace std;

const int N = 5050;

int a[N];
pair<int, int> b[N];
int f[N][N];
int n;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + 1 + n);
    n = unique(a + 1, a + 1 + n) - a - 1;
    int res = 0;
    for (int i = n - 1; i >= 1; --i) {
        for (int j = i + 1; j <= n; ++j) {
            int k = lower_bound(a + 1, a + 1 + n, a[j] * 2 - a[i]) - a;
            f[i][j] = 2;
            if (k <= n && a[k] == a[j] * 2 - a[i]) {
                f[i][j] = 1 + f[j][k];
            }
            res = max(res, f[i][j]);
        }
    }
    cout << res << endl;
}