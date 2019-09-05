#include <bits/stdc++.h>

using namespace std;


int const N = 3;
int const MOD = 1e9 + 7;

struct Matrix
{
    int a[N][N];
    Matrix(){
        memset(a, 0, sizeof(a));
    }
};

Matrix one;

int add_mod(int x, int y) {
    return (x + y) % MOD;
}

int mul_mod(int x, int y) {
    return 1ll * x * y % MOD;
}

int sub_mod(int x, int y) {
    return (x - y + MOD) % MOD;
}

Matrix mul_matrix(Matrix x, Matrix y) {
    Matrix z;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                z.a[i][j] = add_mod(z.a[i][j], mul_mod(x.a[i][k], y.a[k][j]));
            }
        }
    }
    return z;
}

Matrix pow_matrix(Matrix x, long long k) {
    if (k == 0) {
        return one;
    }
    Matrix u = pow_matrix(x, k / 2);
    u = mul_matrix(u, u);
    if (k % 2) {
        u = mul_matrix(u, x);
    }
    return u;
}

int get(long long n, Matrix base) {
    Matrix res;
    res.a[0][0] = res.a[0][1] = res.a[0][2] = 1;

    base = pow_matrix(base, n);
    res = mul_matrix(res, base);
    return res.a[0][2];
}

int main() {
    int test_case;
    cin >> test_case;
    one.a[0][0] = one.a[1][1] = one.a[2][2] = 1;
    Matrix b;
    b.a[0][1] = b.a[1][0] = b.a[1][1] = 1;
    for (int test = 1; test <= test_case; test++) {
        long long l, r, k;
        cin >> l >> r >> k;
        Matrix base = b;
        base = pow_matrix(b, k);
        base.a[0][2] = base.a[0][1];
        base.a[1][2] = base.a[1][1];
        base.a[2][2] = 1;
        base.a[2][0] = base.a[2][1] = 0;

        cout << "Case " << test << ": " << sub_mod(get(r / k, base), get((l - 1) / k, base)) << endl;
    }
}