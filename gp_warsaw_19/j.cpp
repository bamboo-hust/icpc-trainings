#include <bits/stdc++.h>

using namespace std;

const int N = 3030;

void maximize(int &a, int b) {
    if (a < b) a = b;
}

char a[N][N];
int dp[N][N];
int n, m;

bool solve() {
    for (int i = 0; i + 1 < n; ++i) {
        for (int j = 0; j + 1 < m; ++j) if (a[i + 1][j] == a[i][j + 1]) {
            if (i + 2 < n && a[i + 2][j] == a[i + 1][j + 1]) return true;
            if (j + 2 < m && a[i][j + 2] == a[i + 1][j + 1]) return true;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i + 1 < n) maximize(dp[i + 1][j], dp[i][j]);
            if (j + 1 < m) maximize(dp[i][j + 1], dp[i][j]);
            if (i + 1 < n && j + 1 < m && a[i][j + 1] == a[i + 1][j]) {
                maximize(dp[i + 1][j + 1], dp[i][j] + 1);
            }
        }
    }

    return dp[n - 1][m - 1] >= 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> a[i];
    cout << (solve() ? "YES" : "NO") << endl;
}