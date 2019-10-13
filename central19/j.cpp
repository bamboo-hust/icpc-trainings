#include <bits/stdc++.h>

using namespace std;

#define double long double
namespace FFT {
    const int maxf = 1 << 19;
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
    void multiply(int a[], int b[], int na, int nb, int c[], int mod = (int) 1e9 + 7) {
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
    vector<int> multiply(vector<int> a, vector<int> b, int mod = (int) 1e9 + 7) {
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

vector<int> get_prod(vector<int> a) {
    int n = a.size();
    vector<int> b(n, 0);
    for (int i = n - 1; i >= 0; --i) {
        b.push_back(a[i]);
    }
    for (int i = 0; i < n; ++i) a.push_back(0);
    vector<int> c = FFT::multiply(a, b);
    vector<int> res;
    for (int p = 0; p < n; ++p) {
        res.push_back(c[n + n - p - 1]);
    }
    return res;
}

const int N = 1e5 + 5;
const int MOD = 1e9 + 7;

int pre[N];
int suf[N];
int fac[N];
int n, k;

int inverse(int a) {
    int p = MOD - 2;
    int res = 1;
    while (p > 0) {
        if (p & 1) {
            res = 1LL * res * a % MOD;
        }
        a = 1LL * a * a % MOD;
        p >>= 1;
    }
    return res;
}

int C(int k, int n) {
    if (k < 0 || k > n) return 0;

    return 1LL * fac[n] * inverse(fac[k]) % MOD * inverse(fac[n - k]) % MOD;
}

void add(int &a, int b) {
    a += b;
    a %= MOD;
}

void sub(int &a, int b) {
    a -= b;
    a %= MOD;
    a += MOD;
    a %= MOD;
}

int naive(vector<int> a) {
    if (k == 1) return 0;

    int res = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + k - 1; j < n; ++j) {
            add(res, 1LL * C(k - 2, j - i - 1) * (a[i] - a[j]) % MOD * (a[i] - a[j]) % MOD);
        }
    }
    res = 5LL * res % MOD;
    res = 1LL * res * inverse(C(k, n)) % MOD;
    return res;
}

int full(vector<int> a) {
    if (k == 1) {
        return 0;
    }

    vector<int> prod = get_prod(a);

    int res = 0;
    for (int p = k - 1; p < n; ++p) {
        int mul = C(k - 2, p - 1);
        int sum = 0;
        add(sum, suf[p]);
        add(sum, pre[n - 1 - p]);
        sub(sum, 2 * prod[p] % MOD);
        //cerr << p << ' ' << mul << ' ' << prod[p] << ' ' << sum << endl;
        add(res, 1LL * mul * sum % MOD);
    }
    res = 5LL * res % MOD;
    res = 1LL * res * inverse(C(k, n)) % MOD;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(begin(a), end(a));

    // n = 20000;
    // k = 5000;
    // vector<int> a(n);
    // for (int i = 0; i < n; ++i) a[i] = rand() % int(1e9) + 1;


    pre[0] = 1LL * a[0] * a[0] % MOD;
    for (int i = 1; i < n; ++i) {
        pre[i] = pre[i - 1];
        add(pre[i], 1LL * a[i] * a[i] % MOD);
    }

    suf[n] = 0;
    for (int i = n - 1; i >= 0; --i) {
        suf[i] = suf[i + 1];
        add(suf[i], 1LL * a[i] * a[i] % MOD);
    }

    fac[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fac[i] = 1LL * fac[i - 1] * i % MOD;
    }

    //cout << naive(a) << endl;
    cout << full(a) << endl;
}