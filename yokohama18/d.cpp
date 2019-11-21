#include <bits/stdc++.h>

using namespace std;

const int N = 4444;

char a[N];
char b[N];
int f[N][N];
int m;
int n;

int next_a[N][2], next_b[N][2];

void build_next(char s[], int len, int nxt[N][2]) {
    nxt[len + 1][0] = nxt[len + 1][1] = len + 1;
    for (int i = len; i >= 0; --i) {
        for (int j = 0; j <= 1; ++j) {
            if (s[i + 1] - '0' == j) {
                nxt[i][j] = i + 1;
            } else {
                nxt[i][j] = nxt[i + 1][j];
            }
        }
    }
}

int main() {
    cin >> a + 1;
    cin >> b + 1;
    m = strlen(a + 1);
    n = strlen(b + 1);

    build_next(a, m, next_a);
    build_next(b, n, next_b);


    memset(f, 0x3f, sizeof f);
    f[m + 1][n + 1] = 0;
    for (int i = m + 1; i >= 0; --i) {
        for (int j = n + 1; j >= 0; --j) if (i <= m || j <= n){
            for (int k = 0; k <= 1; ++k) {
                f[i][j] = min(f[i][j], f[next_a[i][k]][next_b[j][k]] + 1);
            }
        }
    }

    for (int it = 0, i = 0, j = 0; it < f[0][0]; ++it) {
        for (int k = 0; k <= 1; ++k) {
            int ii = next_a[i][k];
            int jj = next_b[j][k];
            if (f[i][j] == f[ii][jj] + 1) {
                cout << char('0' + k);
                i = ii; j = jj;
                break;
            }
        }
    }
}