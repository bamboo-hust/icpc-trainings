#include <bits/stdc++.h>

using namespace std;

int const N = 1e3 + 5;

int n, a[N][N], ans[N][N];

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char p;
            cin >> p;
            a[i][j] = p - '0';
        }
    }

    for (int u = n; u >= 1; u--) {
        for (int v = u + 1; v <= n; v ++) {
            int sum = 0;
            for (int k = u + 1; k < v; k++) {
                sum = (sum + ans[u][k] * a[k][v]) % 10;
            }
            if (sum != a[u][v]) {
                ans[u][v] = 1;
            } else {
                ans[u][v] = 0;
            }
        }
    }

    for (int u = 1; u <= n; u++) {
        for (int v = 1; v <= n; v++) {
            cout << ans[u][v];
        }
        cout << endl;
    }
    return 0;
}