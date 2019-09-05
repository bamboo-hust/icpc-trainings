#include <bits/stdc++.h>

using namespace std;

int const N = 65;
int const NN = 205;


int const MOD = 1e9 + 7;

int dp[N][N*NN], sum[N][N*NN];


int add_mod(int x, int y) {
    return (x + y) % MOD;
}

int sub_mod(int x, int y) {
    return (x - y + MOD) % MOD;
}

int get_sum(int i, int l, int r) {
    int res = sum[i][r];
    if (l > 0) {
        res = sub_mod(res, sum[i][l - 1]);  
    }
    return res;
}

int mul_mod(int x, int y) {
    return 1ll * x * y % MOD;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) {
            break;
        }
        dp[0][0] = 1;
        for (int j = 0; j <= n * m; j++) {
            sum[0][j] = 1;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= n * m; j++) {
                dp[i][j] = get_sum(i - 1, j - m, j);
                if (j) {
                    sum[i][j] = add_mod(sum[i][j - 1], dp[i][j]);
                } else {
                    sum[i][j] = dp[i][j];
                }
            }
        }

        int ans = 0;
        for (int j = 0; j <= m; j++) {
            int total = j * (n - 1);
            ans = add_mod(ans, mul_mod(dp[n - 1][total], n));
        }

        cout << ans << endl;
    }
}