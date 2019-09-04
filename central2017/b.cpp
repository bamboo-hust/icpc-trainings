#include <bits/stdc++.h>

using namespace std;

int m;

struct Matrix {
    int a[2][2];
    Matrix(int dia = 0) {
        a[0][0] = a[1][1] = dia;
        a[0][1] = a[1][0] = 0;
    }
};

int mul(int a, int b) {
    return ((long long) a * b) % m;
}

int add(int a, int b) {
    a += b;
    if (a >= m) {
        a -= m;
    }
    return a;
}

Matrix matrixMul(const Matrix &u, const Matrix &v) {
    Matrix res(0);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                res.a[i][j] = add(res.a[i][j], mul(u.a[i][k], v.a[k][j]));
            }
        }
    }
    return res;
}

Matrix matrixPow(Matrix u, long long v) {
    Matrix res(1);
    while (v) {
        if (v & 1) {
            res = matrixMul(res, u);
        }
        u = matrixMul(u, u);
        v >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    long long t;
    cin >> t >> m;
    if (t == 1) {
        cout << 7 % m << endl;
        return 0;
    }
    Matrix foo(0);
    foo.a[0][0] = 8 % m;
    foo.a[0][1] = 2 % m;
    Matrix bar(0);
    bar.a[0][0] = 8 % m;
    bar.a[0][1] = 1 % m;
    bar.a[1][0] = ((-5 % m) + m) % m;
    Matrix res = matrixMul(foo, matrixPow(bar, t - 1));
    cout << (res.a[0][0] - 1 + m) % m << endl;
    return 0;
}