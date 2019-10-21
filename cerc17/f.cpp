#include <bits/stdc++.h>

using namespace std;

const int N = 10000010;

inline int mul(int u, int v, int p) {
    return (long long) u * v % p;
}

inline int power(int u, int v, int p) {
    int res = 1;
    while (v) {
        if (v & 1) res = mul(res, u, p);
        u = mul(u, u, p);
        v >>= 1;
    }
    return res;
}

inline int inv(int u, int p) {
    return power(u, p - 2, p);
}

int f[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n;
    int p, r;
    cin >> n >> p >> r;
    f[0] = 1;
    for (int i = 1; i <= p; i++) f[i] = mul(f[i - 1], i, p);
    if (n < p) {
        if (r == 0)  cout << -1 << ' ' << -1 << endl;
        else {
            int invN = inv(f[n], p);
            for (int i = 1; i <= n; i++) {
                int u = mul(r, i, p);
                u = mul(u, invN, p);
                if (u < i) {
                    cout << i << ' ' << u << endl;
                    return 0;
                }
            }
            cout << -1 << ' ' << -1 << endl;
        }
        return 0;
    }
    if (n == p) {
        if (r == 0) {
            if (p == 2) cout << -1 << ' ' << -1 << endl;
            else cout << 2 << ' ' << 1 << endl;
        }
        else {
            int x = mul(r, inv(f[p - 1], p), p);
            cout << p << ' ' << x << endl;
        }
        return 0;
    }
    if (r == 0) {
        cout << n << ' ' << n - 1 << endl;
        return 0;
    }
    if (n >= p * 2) {
        cout << -1 << ' ' << -1 << endl;
        return 0;
    }
    int x = mul(f[p - 1], f[n % p], p);
    x = mul(r, inv(x, p), p);
    cout << p << ' ' << x << endl;
    return 0;
}