//
// Created by quanglm1998 on 26/09/2019.
//

#include <bits/stdc++.h>

using namespace std;

const int N = 35010;
const int DELTA = 500;
const long long INF = (1ll << 60);

int n, k;
int a[N][10];
int id[N];
long long dp[2][DELTA * 2];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k * 2 + 1; j++) {
            cin >> a[i][j];
        }
        id[i] = i;
    }
    long long res = INF;
    srand(25011998);
    for (int it = 1; it <= 5; it++) {
        random_shuffle(id + 1, id + n + 1);
        for (int j = 0; j < DELTA * 2; j++) dp[0][j] = INF;
        dp[0][DELTA] = 0;
        int cur = 0;
        for (int i = 0; i < n; i++, cur ^= 1) {
            for (int j = 0; j < DELTA * 2; j++) dp[cur ^ 1][j] = INF;
            int u = id[i + 1];
            for (int j = 0; j < DELTA * 2; j++) {
                if (dp[cur][j] >= INF) continue;
                for (int now = 1; now <= k * 2 + 1; now++) {
                    int val = now - k - 1;
                    if (j + val >= 0 && j + val < DELTA * 2) {
                        dp[cur ^ 1][j + val] = min(dp[cur ^ 1][j + val], dp[cur][j] + a[u][now]);
                    }
                }
            }
        }
        res = min(res, dp[cur][DELTA]);
    }
    cout << res << endl;
    return 0;
}