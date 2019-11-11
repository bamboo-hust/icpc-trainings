#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int MOD = 1000000007;

struct Matrix {
    int a[2][2];

    Matrix() {
        memset(a, 0, sizeof a);
    }

    int* operator [] (int i) {
        return a[i];
    }

    void swap(Matrix &o) {
        for (int i = 0; i <= 1; ++i) {
            for (int j = 0; j <= 1; ++j) {
                std::swap(a[i][j], o.a[i][j]);
            }
        }
    }
};

ostream& operator << (ostream& out, Matrix a) {
    out << "{" << a[0][0] << ' ' << a[0][1] << endl;
    out << " " << a[1][0] << ' ' << a[1][1] << "}" << endl;
    return out;
}

Matrix IDENTITY;

Matrix operator * (Matrix a, Matrix b) {
    Matrix c;
    for (int i = 0; i <= 1; ++i) {
        for (int j = 0; j <= 1; ++j) {
            for (int k = 0; k <= 1; ++k) {
                c[i][j] += (1LL * a[i][k] * b[k][j]) % MOD;
                if (c[i][j] >= MOD) c[i][j] -= MOD;
            }
        }
    }
    return c;
}

Matrix f[N * 4][2];

bool inv[N * 4];
char s[N];
int n, q;

void assign(int a[2][2], const vector<int> v) {
    a[0][0] = v[0];
    a[0][1] = v[1];
    a[1][0] = v[2];
    a[1][1] = v[3];
}

void push(int k, int l, int r) {
    if (inv[k]) {
        f[k][0].swap(f[k][1]);
        inv[k] = false;
        if (l != r) {
            inv[k * 2] ^= 1;
            inv[k * 2 + 1] ^= 1;
        }
    }
}

void pull(int k, int l, int r) {
    if (l != r) {
        f[k][0] = f[k * 2 + 1][0] * f[k * 2][0];
        f[k][1] = f[k * 2 + 1][1] * f[k * 2][1];
    }
}

void init(int k, int l, int r) {
    if (l == r) {
        if (s[l] == 'A') {
            assign(f[k][0].a, {1, 1, 0, 1});
            assign(f[k][1].a, {1, 0, 1, 1});
        } else {
            assign(f[k][0].a, {1, 0, 1, 1});
            assign(f[k][1].a, {1, 1, 0, 1});
        }
    } else {
        init(k * 2, l, l + r >> 1);
        init(k * 2 + 1, (l + r >> 1) + 1, r);
        pull(k, l, r);
    }
}

void flip(int k, int l, int r, int i, int j) {
    push(k, l, r);
    if (j < l || r < i) return;
    if (i <= l && r <= j) {
        inv[k] = true;
        push(k, l, r);
        return;
    }
    flip(k * 2, l, l + r >> 1, i, j);
    flip(k * 2 + 1, (l + r >> 1) + 1, r, i, j);
    pull(k, l, r);
}

Matrix get(int k, int l, int r, int i, int j) {
    push(k, l, r);
    if (j < l || r < i) return IDENTITY;
    if (i <= l && r <= j) return f[k][0];
    return get(k * 2 + 1, (l + r >> 1) + 1, r, i, j) * get(k * 2, l, l + r >> 1, i, j);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    assign(IDENTITY.a, {1, 0, 0, 1});

    cin >> n >> q >> s + 1;

    init(1, 1, n);

    while (q--) {
        int cmd, l, r;
        cin >> cmd >> l >> r;
        if (cmd == 1) {
            flip(1, 1, n, l, r);
        } else {
            int a0, b0;
            cin >> a0 >> b0;
            Matrix A = get(1, 1, n, l, r);
            cout << (1LL * A[0][0] * a0 + 1LL * A[0][1] * b0) % MOD << ' ' << (1LL * A[1][0] * a0 + 1LL * A[1][1] * b0) % MOD << '\n';
        }
    }

    return 0;
}