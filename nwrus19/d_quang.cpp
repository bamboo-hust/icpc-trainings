#include <bits/stdc++.h>

using namespace std;

const int N = 100010;
const int MOD = 998244353;

inline int add(int u, int v) {
    return (u += v) >= MOD ? u - MOD : u;
}
 
inline int sub(int u, int v) {
    return (u -= v) < 0 ? u + MOD : u;
}
 
inline int mul(int u, int v) {
    return (long long)u * v % MOD;
}
 
inline int power(int u, int v) {
    int res = 1;
    while (v) {
        if (v & 1) res = mul(res, u);
        u = mul(u, u);
        v >>= 1;
    }
    return res;
}
 
inline int inv(int u) {
    return power(u, MOD - 2);
}

int n, k;
int r[N], d[N];
int res;

inline int getCeil(int u, int v) {
    if (u % v == 0) return u / v;
    return u / v + 1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    r[1] = k;
    r[2] = add(k, mul(k, k));
    for (int i = 2; i <= n; i++) {
        int now = add(power(k, getCeil(i - 2, 2)), power(k, getCeil(i - 1, 2)));
        r[i] = mul(k, add(r[i - 2], now));
    }
    for (int i = 1; i <= n; i++) {
        d[i] = sub(r[i], d[i]);
        for (int j = i + i; j <= n; j += i) {
            d[j] = add(d[j], mul(d[i], j / i));
        }
        res = add(res, mul(n / i, d[i]));
    }
    cout << res << endl;
    return 0;
}