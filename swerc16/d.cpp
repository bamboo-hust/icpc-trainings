#include <bits/stdc++.h>

using namespace std;

using LD = long double;

const int N = 55;

LD C[N][N];
LD E[N][N][N];

int AB, A, B;
int n, d, c;

void initComb() {
    for (int i = 0; i < N; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
}

LD solve() {
    for (int ab = AB; ab >= 0; --ab) {
        for (int a = A; a >= 0; --a) {
            for (int b = B; b >= 0; --b) {
                if (a + ab == c || b + ab == c) {
                    E[ab][a][b] = 0;
                    continue;
                }
                E[ab][a][b] = 0;
                for (int x = 0; x <= AB - ab && x <= d; ++x) {
                    for (int y = 0; y <= A - a && x + y <= d; ++y) {
                        for (int z = 0; z <= B - b && x + y + z <= d; ++z) if (x || y || z) {
                            E[ab][a][b] += E[ab + x][a + y][b + z] * (C[AB - ab][x] * C[A - a][y] * C[B - b][z] * C[n - (AB-ab) - (A-a) - (B-b)][d - x - y - z] / C[n][d]);
                        }
                    }
                }

                E[ab][a][b] = (E[ab][a][b] + 1) / (1 - (C[AB - ab][0] * C[A - a][0] * C[B - b][0] * C[n - (AB-ab) - (A-a) - (B-b)][d] / C[n][d]));
            }
        }
    }
    return E[0][0][0];
}

int main() {
    initComb();

    cin >> n >> d >> c;
    vector<int> P(c), Q(c);
    for (int i = 0; i < c; ++i) cin >> P[i];
    for (int i = 0; i < c; ++i) cin >> Q[i];
    vector<int> mask(n + 1);
    for (int i = 0; i < c; ++i) {
        mask[P[i]] |= 1;
        mask[Q[i]] |= 2;
    }
    for (int i = 1; i <= n; ++i) {
        if (mask[i] == 3) ++AB;
        if (mask[i] == 1) ++A;
        if (mask[i] == 2) ++B;
    }
    cout << setprecision(5) << fixed << solve() << endl;
}