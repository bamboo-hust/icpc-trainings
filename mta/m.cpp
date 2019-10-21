#include <bits/stdc++.h>

using namespace std;

const int N = 100;
const int HALF = 50;

char land[N][N];
char a[N][N];
char b[N][N];
int n, m;

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> a[i][j];
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> b[i][j];

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            land[i][j] = '.';
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            land[HALF + i][HALF + j] = b[i][j];
        }
    }

    int res = 0;
    for (int i = 1; i + n < N; ++i) {
        for (int j = 1; j + m < N; ++j) {
            int cur = 0;
            bool ok = true;
            for (int x = 0; x < n; ++x) {
                for (int y = 0; y < m; ++y) if (a[x][y] == 'H') {
                    if (land[i + x][j + y] != '.') {
                        ok = false;
                        break;
                    }
                    for (int u = i + x - 1; u <= i + x + 1; ++u) {
                        for (int v = j + y - 1; v <= j + y + 1; ++v) {
                            if (u == i + x || v == j + y) {
                                cur += land[u][v] == 'W';
                            }
                            //cerr << "match " << u << ' ' << v << endl;
                        }
                    }
                }
                if (!ok) break;
            }
            if (ok) {
                res = max(res, cur);
            }
        }
    }

    cout << res << endl;
}