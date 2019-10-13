#include <bits/stdc++.h>

using namespace std;

const int N = 2e6 + 6;

int n, k;
char s[N][2];

int dp[N][2];
int trace[N][2];
bool in_path[N][2];

int main() {
    ios::sync_with_stdio(false);

    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> s[i][0];
    for (int i = 1; i <= n; ++i) cin >> s[i][1];

//    for (int i = 1; i <= n; ++i) cout << s[i][0]; cout << endl;
//    for (int i = 1; i <= n; ++i) cout << s[i][1]; cout << endl;

    dp[1][0] = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= 1; ++j) if (dp[i][j]) {
            //cerr << i << ' ' << j << ' ' << dp[i][j] << endl;
            if (s[i + 1][j] == '.' && dp[i + 1][j] < dp[i][j] + 1) {
                dp[i + 1][j] = dp[i][j] + 1;
                trace[i + 1][j] = 0;
            }
            if (s[i + 1][!j] == '.' && s[i + 1][j] == '.' && dp[i + 1][!j] < dp[i][j] + 2) {
                dp[i + 1][!j] = dp[i][j] + 2;
                trace[i + 1][!j] = 1;
            }
            if (s[i + 1][!j] == '.' && s[i][!j] == '.' && dp[i + 1][!j] < dp[i][j] + 2) {
                dp[i + 1][!j] = dp[i][j] + 2;
                trace[i + 1][!j] = 2;
            }
        }
    }

    int res = dp[n][1];

    int cur_row = 1;
    for (int i = n; i >= 1; --i) {
        in_path[i][cur_row] = true;
        if (i == 1) break;
        if (trace[i][cur_row] == 1) {
            in_path[i][!cur_row] = true;
            cur_row = !cur_row;
        } else if (trace[i][cur_row] == 2) {
            in_path[i - 1][cur_row] = true;
            cur_row = !cur_row;
        }
    }

    cout << res << endl;
    for (int i = 1; i <= n; ++i) cout << in_path[i][0]; cout << endl;
    for (int i = 1; i <= n; ++i) cout << in_path[i][1]; cout << endl;

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= 1; ++j) if (in_path[i][j] && in_path[i + 1][j] && !in_path[i][!j]) {
            if (k <= 0) break;
            if (i == 1 && j == 1) continue;
            if ((s[i][!j] == '.') != (s[i + 1][!j] == '.')) {
                cerr << "fire " << i << ' ' << j << endl;
                s[i][!j] = s[i + 1][!j] = '.';
                in_path[i][!j] = in_path[i + 1][!j] = true;
                res += 2;
                --k;
            }
        }
    }

    cout << res << endl;
    for (int i = 1; i <= n; ++i) cout << in_path[i][0]; cout << endl;
    for (int i = 1; i <= n; ++i) cout << in_path[i][1]; cout << endl;

    for (int i = 1; i + 1 < n; ++i) {
        for (int j = 0; j <= 1; ++j) if (in_path[i][j] && in_path[i + 1][j] && in_path[i + 1][!j] && in_path[i + 2][!j] && !in_path[i][!j]) {
                if (k <= 0) break;
                if ((s[i][!j] == '.') != (s[i + 2][j] == '.')) {
                    //cerr << "fire " << i << ' ' << j << endl;
                    s[i][!j] = s[i + 2][j] = '.';
                    in_path[i][!j] = in_path[i + 2][j] = true;
                    res += 2;
                    --k;
                }
            }
    }

    // cout << res << endl;
    // for (int i = 1; i <= n; ++i) cout << in_path[i][0]; cout << endl;
    // for (int i = 1; i <= n; ++i) cout << in_path[i][1]; cout << endl;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= 1; ++j) if (in_path[i][j] && in_path[i + 1][j]) {
            if (k <= 1) break;
            if (s[i][!j] == '#' && s[i + 1][!j] == '#') {
                s[i][!j] = s[i + 1][!j] = '.';
                in_path[i][!j] = in_path[i + 1][!j] = true;
                res += 2;
                k -= 2;
            }
        }
    }

    cout << res << endl;
    for (int i = 1; i <= n; ++i) cout << in_path[i][0]; cout << endl;
    for (int i = 1; i <= n; ++i) cout << in_path[i][1]; cout << endl;
}