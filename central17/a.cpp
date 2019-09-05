#include <bits/stdc++.h>

using namespace std;

const int N = 1111;

char a[N][N];
int r[N][N], c[N][N];
int n, m;

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        cin >> m >> n;
        for (int i = 1; i <= m; ++i) {
            cin >> (a[i] + 1);
        }
        memset(r, 0, sizeof r);
        memset(c, 0, sizeof c);
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) if (a[i][j] != '0') {
                r[i][a[i][j] - '1'] += 1;
                c[j][a[i][j] - '1'] += 1;
            }
        }
        long long ans = 0;
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) if (a[i][j] != '0') {
                int x = a[i][j] - '1';
                ans += r[i][x ^ 1] * c[j][x ^ 1];
            }
        }
        cout << ans << '\n';
    }
    return 0;
}