#include <bits/stdc++.h>

using namespace std;

const int N = 2010;

int n, m;
char a[N], b[N];
int f[N][N], g[N][N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> (a + 1);
        cin >> (b + 1);
        n = strlen(a + 1);
        m = strlen(b + 1);

        for (int i = 1; i <= m; i++) f[0][i] = i;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (a[i] == b[j]) {
                    f[i][j] = g[i][j - 1];
                    g[i][j] = f[i - 1][j];
                } else {
                    f[i][j] = max(f[i - 1][j], g[i][j - 1]);
                    g[i][j] = min(f[i - 1][j], g[i][j - 1]);
                }
            }
        }

        int q;
        cin >> q;
        for (int i = 1; i <= q; i++) {
            int l, r, k;
            cin >> l >> r >> k;
            int res = 0;
            for (int j = l; j <= r; j++) res += (f[k][j] < l);
            cout << res << ' ';
        }
        cout << '\n';
    }
    return 0;
}