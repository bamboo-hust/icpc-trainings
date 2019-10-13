#include <bits/stdc++.h>

using namespace std;
int const MOD = 1e6 + 3;

int const N = 4e5 + 5;

int l[N], t[N];

int pow_a[N], pow_b[N], fact[N];

int mul_mod(int x, int y) {
    return 1ll * x * y % MOD;
}

int add_mod(int x, int y) {
    return (x + y) % MOD;
}

int sub_mod(int x, int y) {
    return (x - y + MOD) % MOD;
}

int pow_mod(int x, int y) {
    if (y == 0) {
        return 1;
    }
    int u = pow_mod(x, y / 2);
    u = mul_mod(u, u);
    if (y & 1) {
        u = mul_mod(u, x);
    }
    return u;
}

int C(int x, int y) {
    return mul_mod(fact[y], pow_mod(mul_mod(fact[x], fact[y - x]), MOD - 2));
}


vector < int > mul_naive(vector < int > a, vector < int > b) {
    vector < int > c;
    c.resize(a.size() + b.size() - 1);
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            c[i + j] = add_mod(c[i + j], mul_mod(a[i], b[j]));
        }
    }
    return c;
}

void normalize(vector<int> &A, vector<int> &B) {
    if (A.size() < B.size()) A.resize(B.size());
    if (B.size() < A.size()) B.resize(A.size());
}

vector<int> operator + (vector<int> A, vector<int> B) {
    normalize(A, B);
    vector<int> C(A.size());
    for (int i = 0; i < C.size(); ++i) {
        C[i] = add_mod(A[i], B[i]);
    }
    return C;
}

vector<int> operator - (const vector<int> &A, const vector<int> &B) {
    vector<int> C(min(A.size(), B.size()));
    for (int i = 0; i < C.size(); ++i) {
        C[i] = sub_mod(A[i], B[i]);
    }
    return C;
}

void split(vector<int> &A, int cut, vector<int> &L, vector<int> &R) {
    L = vector<int>(A.begin(), A.begin() + cut);
    R = vector<int> (A.begin() + cut, A.end());
}

vector<int> shift(vector<int> &A, int n) {
    vector<int> res(n, 0);
    res.insert(res.end(), A.begin(), A.end());
    return res;
}

void fix(vector<int> &A) {
    while (A.size() > 1 && A.back() == 0) A.pop_back();
}


#define double long double
namespace FFT {
    const int maxf = 1 << 20;
    struct cp {
        double x, y;
        cp(double x = 0, double y = 0) : x(x), y(y) {}
        cp operator + (const cp& rhs) const {
            return cp(x + rhs.x, y + rhs.y);
        }
        cp operator - (const cp& rhs) const {
            return cp(x - rhs.x, y - rhs.y);
        }
        cp operator * (const cp& rhs) const {
            return cp(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x);
        }
        cp operator !() const {
            return cp(x, -y);
        }
    } rts[maxf + 1];
    cp fa[maxf], fb[maxf];
    cp fc[maxf], fd[maxf];

    int bitrev[maxf];
    void fftinit() {
        int k = 0; while ((1 << k) < maxf) k++;
        bitrev[0] = 0;
        for (int i = 1; i < maxf; i++) {
            bitrev[i] = bitrev[i >> 1] >> 1 | ((i & 1) << k - 1);
        }
        double PI = acos((double) -1.0);
        rts[0] = rts[maxf] = cp(1, 0);
        for (int i = 1; i + i <= maxf; i++) {
            rts[i] = cp(cos(i * 2 * PI / maxf), sin(i * 2 * PI / maxf));
        }
        for (int i = maxf / 2 + 1; i < maxf; i++) {
            rts[i] = !rts[maxf - i];
        }
    }
    void dft(cp a[], int n, int sign) {
        static int isinit;
        if (!isinit) {
            isinit = 1;
            fftinit();
        }
        int d = 0; while ((1 << d) * n != maxf) d++;
        for (int i = 0; i < n; i++) {
            if (i < (bitrev[i] >> d)) {
                swap(a[i], a[bitrev[i] >> d]);
            }
        }
        for (int len = 2; len <= n; len <<= 1) {
            int delta = maxf / len * sign;
            for (int i = 0; i < n; i += len) {
                cp *x = a + i,*y = a + i + (len >> 1), *w = sign > 0 ? rts : rts + maxf;
                for (int k = 0; k + k < len; k++) {
                    cp z = *y * *w;
                    *y = *x - z, *x = *x + z;
                    x++, y++, w += delta;
                }
            }
        }
        if (sign < 0) {
            for (int i = 0; i < n; i++) {
                a[i].x /= n;
                a[i].y /= n;
            }
        }
    }
    void multiply(int a[], int b[], int na, int nb, long long c[]) {
        int n = na + nb - 1; while (n != (n & -n)) n += n & -n;
        for (int i = 0; i < n; i++) fa[i] = fb[i] = cp();
        for (int i = 0; i < na; i++) fa[i] = cp(a[i]);
        for (int i = 0; i < nb; i++) fb[i] = cp(b[i]);
        dft(fa, n, 1), dft(fb, n, 1);
        for (int i = 0; i < n; i++) fa[i] = fa[i] * fb[i];
        dft(fa, n, -1);
        for (int i = 0; i < n; i++) c[i] = (long long) floor(fa[i].x + 0.5);
    }
    void multiply(int a[], int b[], int na, int nb, int c[], int mod) {
        int n = na + nb - 1;
        while (n != (n & -n)) n += n & -n;
        for (int i = 0; i < n; i++) fa[i] = fb[i] = cp();
        static const int magic = 15;
        for (int i = 0; i < na; i++) fa[i] = cp(a[i] >> magic, a[i] & (1 << magic) - 1);
        for (int i = 0; i < nb; i++) fb[i] = cp(b[i] >> magic, b[i] & (1 << magic) - 1);
        dft(fa, n, 1), dft(fb, n, 1);
        for (int i = 0; i < n; i++) {
            int j = (n - i) % n;
            cp x = fa[i] + !fa[j];
            cp y = fb[i] + !fb[j];
            cp z = !fa[j] - fa[i];
            cp t = !fb[j] - fb[i];
            fc[i] = (x * t + y * z) * cp(0, 0.25);
            fd[i] = x * y * cp(0, 0.25) + z * t * cp(-0.25, 0);
        }
        dft(fc, n, -1), dft(fd, n, -1);
        for (int i = 0; i < n; i++) {
            long long u = ((long long) floor(fc[i].x + 0.5)) % mod;
            long long v = ((long long) floor(fd[i].x + 0.5)) % mod;
            long long w = ((long long) floor(fd[i].y + 0.5)) % mod;
            c[i] = ((u << 15) + v + (w << 30)) % mod;
        }
    }
    vector<int> multiply(vector<int> a, vector<int> b, int mod) {
        //if (max(a.size(), b.size()) < 128) return mul_naive(a, b);
        static int fa[maxf], fb[maxf], fc[maxf];
        int na = a.size(), nb = b.size();
        for (int i = 0; i < na; i++) fa[i] = a[i];
        for (int i = 0; i < nb; i++) fb[i] = b[i];
        multiply(fa, fb, na, nb, fc, mod);
        int k = na + nb - 1;
        vector<int> res(k);
        for (int i = 0; i < k; i++) res[i] = fc[i];
        return res;
    }
}

vector<int> operator * (vector<int> A, vector<int> B) {
    normalize(A, B);
    int n = A.size();
    if (n <= 7000) return FFT::multiply(A, B, MOD);
    int mid = n >> 1;
    vector<int> AL, AR, BL, BR;
    split(A, mid, AL, AR);
    split(B, mid, BL, BR);
    vector<int> a = AR * BR;
    vector<int> c = AL * BL;
    vector<int> b = (AL + AR) * (BL+ BR) - (a + c);
    vector<int> res = shift(a, mid + mid) + shift(b, mid) + c;
    fix(res);
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int n, a, b, c;
    cin >> n >> a >> b >> c;

    pow_a[0] = pow_b[0] = fact[0] = 1;
    for (int i = 1; i < N; i++) {
        pow_a[i] = mul_mod(pow_a[i - 1], a);
        pow_b[i] = mul_mod(pow_b[i - 1], b);
        fact[i] = mul_mod(fact[i - 1], i);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        cin >> l[i];
        if (i > 1) {
            ans = add_mod(ans, mul_mod(a, mul_mod(C(n - i, n - 2 + n - i), mul_mod(mul_mod(l[i], pow_a[n - 2]), pow_b[n - i]))));
        }
    }


    for (int i = 1; i <= n; i++) {
        cin >> t[i];
        if (i > 1) {
            ans = add_mod(ans, mul_mod(b, mul_mod(C(n - i, n - 2 + n - i), mul_mod(mul_mod(t[i], pow_b[n - 2]), pow_a[n - i]))));
        }
    }

    vector < int > pa, pb;
    pa.resize(n - 1);
    pb.resize(n - 1);
    for (int i = 0; i <= n - 2; i++) {
        pa[i] = mul_mod(pow_a[i], pow_mod(fact[i], MOD - 2));
        pb[i] = mul_mod(pow_b[i], pow_mod(fact[i], MOD - 2));
    }

    //vector < int > d = FFT::multiply(pa, pb, MOD);
    vector < int > d = pa * pb;

    for (int i = 0; i < d.size(); i++) {
        ans = add_mod(ans, mul_mod(mul_mod(fact[i], d[i]), c));
    }
//    for (int i = 0; i <= n - 2; i++) {
//        for (int j = 0; j <= n - 2; j++) {
//            ans = add_mod(ans, mul_mod(mul_mod(mul_mod(C(i, i + j), pow_a[i]), pow_b[j]), c));
//        }
//    }

    cout << ans << endl;




}