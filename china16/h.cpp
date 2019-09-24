#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007;

inline int add(int u, int v) {
    return (u += v) >= MOD ? u - MOD : u;
}

inline int mul(int u, int v) {
    return (long long)u * v % MOD;
}

inline int power(int u, int v) {
    int res = 1;
    while (v) {
        if (v & 1) res = mul(res, u);
        u = mul(u, u);
        v >>=1;
    }
    return res;
}


int main() {
    int tc;
    cin >> tc;
    for (int test = 1; test <= tc; test++) {
        cout << "Case #" << test << ": ";
        int n, m, k;
        cin >> n >> m >> k;
        int res = power(k, n * m);
        for (int i = 1; i <= k; i++) {
            int now = power(i - 1, n + m - 2);
            now = mul(now, power(k, (n - 1) * (m - 1)));
            now = mul(now, mul(n, m));
            res = add(res, now);
        }
        cout << res << endl;
    }
    return 0;   
}