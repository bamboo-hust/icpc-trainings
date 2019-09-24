#include <bits/stdc++.h>

using namespace std;

namespace IP {
    const int MOD = 1e9 + 7;
    const int N = 16;

    int a[N];
    int fact[N];
    int ifact[N];
    int prf[N];
    int suf[N];

    int fpow(int n, int k) {
        int r = 1;
        for (; k; k >>= 1) {
            if (k & 1) r = 1LL * r * n % MOD;
            n = 1LL * n * n % MOD;
        }
        return r;
    }

    void update(int u, int v) {
        a[u] = v;
    }

    void build() {
        fact[0] = ifact[0] = 1;
        for (int i = 1; i < N; ++i) {
            fact[i] = 1LL * fact[i - 1] * i % MOD;
            ifact[i] = fpow(fact[i], MOD - 2);
        }
    }

    int calc(int x, int k) {
        prf[0] = suf[k + 1] = 1;
        for (int i = 1; i <= k; ++i) {
            prf[i] = 1LL * prf[i - 1] * (x - i + MOD) % MOD;
        }
        for (int i = k; i >= 1; --i) {
            suf[i] = 1LL * suf[i + 1] * (x - i + MOD) % MOD;
        }
        int res = 0;
        for (int i = 1; i <= k; ++i) {
            if (!(((k - i) & 1))) {
                res = (res + 1LL * prf[i - 1] * suf[i + 1] % MOD * ifact[i - 1] % MOD * ifact[k - i] % MOD * a[i]) % MOD;
            } else {
                res = (res - 1LL * prf[i - 1] * suf[i + 1] % MOD * ifact[i - 1] % MOD * ifact[k - i] % MOD * a[i] % MOD + MOD) % MOD;
            }
        }
        return res;
    }
}

int gen(int x) {
    return x * x + 2 * x + 1;
    //return x * x * x * x * 10 + 2 * x * x * x + x * x + 2 * x + 2;
}

int main() {
    IP::build();
    for (int i = 1;; ++i) {
        cout << "ask " << i << endl;
        cin >> IP::a[i];
        //IP::a[i] = gen(i); cerr << IP::a[i] << endl;
        int last = IP::calc(i, i - 1);
        int now = IP::calc(i, i);
        if (i > 1 && last == now) {
            cout << "degree " << i - 2 << endl;
            return 0;
        }
    }
}