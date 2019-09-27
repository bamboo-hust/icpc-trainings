#include <bits/stdc++.h>

using namespace std;

using Matrix = vector< vector<int> >;

const int MOD = 1e9;
const int K = 16;

void add(int &a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

Matrix operator * (const Matrix &a, const Matrix &b) {
    Matrix c(a.size(), vector<int>(b[0].size()));
    for (int i = 0; i < c.size(); ++i) {
        for (int j = 0; j < c[i].size(); ++j) {
            for (int k = 0; k < a[0].size(); ++k) {
                add(c[i][j], 1LL * a[i][k] * b[k][j] % MOD);
            }
        }
    }
    return c;
}

Matrix operator ^ (Matrix a, uint64_t n) {
    Matrix res(a.size(), vector<int>(a.size()));
    for (int i = 0; i < res.size(); ++i) res[i][i] = 1;
    while (n > 0) {
        if (n & 1) {
            res = res * a;
        }
        a = a * a;
        n >>= 1;
    }
    return res;
}

int C[K][K];

int S(uint64_t n, int k) {
    if (n == 0) {
        return 1;
    }

    if (n == 1) {
        return 2;
    }

    Matrix a(k + 2, vector<int>(k + 2));
    for (int i = 0; i <= k; ++i) {
        for (int j = 0; j <= k; ++j) {
            a[i][j] = C[k - i][j];
        }
    }
    for (int i = 0; i <= k; ++i) {
        a[k + 1][i] = C[k][i];
    }
    a[k + 1][k + 1] = 1;

    Matrix v(k + 2, vector<int>(1, 1));
    for (int i = 0; i <= k; ++i) {
        v[i][0] = 1 << k;
    }
    v[k + 1][0] = (1 << k) + (1 << k);

    Matrix A = a ^ (n - 1);
    Matrix ans = A * v;

    return ans.back()[0];
}

int main() {
    for (int i = 0; i < K; ++i) {
        C[i][0] = 1;
        if (i > 0) {
            for (int j = 1; j < K; ++j) {
                C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            }
        }
    }

    uint64_t n;
    int k;
    cin >> n >> k;

    int res = 0;
    for (int j = 0; j <= k; ++j) {
        int mul = 1;
        if ((k - j) % 2) mul = -1;
        int cur = 1LL * C[k][j] * mul * S(n, j) % MOD;
        add(cur, MOD);
        add(res, cur);
    }

    cout << setw(9) << setfill('0') << res << endl;
}