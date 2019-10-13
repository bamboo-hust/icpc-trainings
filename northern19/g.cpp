#include <bits/stdc++.h>

using namespace std;

int const N = 1e3 + 5;
int const NN = 4e3 + 5;

bitset < NN > pre[N], dp[N];

int a[N][N];



int main() {
    ios_base::sync_with_stdio(0);
    int t, n, m;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        for (int j = 1; j <= m; j++) {
            pre[j].reset();
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                char p;
                cin >> p;
                a[i][j] = p - '0';
            }
        }
        pre[1][0] = 1;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                dp[j].reset();
                if (j > 1) {
                    dp[j] |= (dp[j - 1] << a[i][j]);
                }

                dp[j] |= (pre[j] << a[i][j]);
            }

            for (int j = 1; j <= m; j++) {
                pre[j] = dp[j];
            }
        }

        for (int i = 0; i < NN; i++) {
            if (dp[m][i] == 1) {
                cout << i << " ";
            }
        }
        cout << "\n";
    }
}