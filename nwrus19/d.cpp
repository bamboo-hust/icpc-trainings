#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
const int N = 1e5 + 5;

int add(int u, int v) {
    return (u + v) % MOD;
}

int mul(int u, int v) {
    return 1LL * u * v % MOD;
}

int sub(int u, int v) {
    return (u - v + MOD) % MOD;
}

int p[N];
int f[N];
int n, k;

int C(int n, int k) {
    if (k > n) return 0;
    int res = 1;
    for (int i = n; i > n - k; --i) {
        res = res * i;
    }
    for (int i = 2; i <= k; ++i) {
        res = res / i;
    }
    return res % MOD;
}

int get_res(int n) {
    int res = 0;
    for (int i = 1; i < n; ++i) {
        res = add(res, mul(f[i], p[(n - i + 1) / 2]));
    }
    for (int l = 2; l < n; ++l) if (n % (l - 1) == 0) {
        res = sub(res, f[(l + 1) / 2]);
    }

    //res = add(res, p[(n + 1) / 2]);


    vector<int> minus(n + 1);
    for (int i = 1; i <= n; ++i) minus[i] = f[i];

    for (int k = 1; k <= n; ++k) if (n % k == 0) {
        for (int j = k + k; j <= n; j += k) {
            minus[j] -= minus[k];
        }
    }

    for (int l = 1; l < n; ++l) if (n % l == 0) {
        //res = sub(res, minus[l]);
    }
    return res;
}

bool is_palin(string s) {
    string t = s;
    reverse(begin(t), end(t));
    return s == t;
}

string simul(int n, int l) {
    string a(n, '\0');
    auto match = [&](int i, int j) {
        if (bool(a[i]) != bool(a[j])) {
            if (a[i]) {
                a[j] = a[i];
            } else {
                a[i] = a[j];
            }
            return true;
        }
        return false;
    };
    char now = '0';
    while (true) {
        bool found = false;
        for (int i = 1; i < n; ++i) {
            found |= match(i, n - i);
        }
        for (int i = 0; i < l; ++i) {
            found |= match(i, l - i - 1);
        }
        for (int i = l; i < n; ++i) {
            found |= match(i, n - (i - l) - 1);
        }
        if (!found) {
            for (int i = 0; i < n; ++i) {
                if (!a[i]) {
                    a[i] = now;
                    found = true;
                    break;
                }
            }
            ++now;
        }
        if (!found) break;
    }
    if (!is_palin(a.substr(1))) return "NONE";
    if (!is_palin(a.substr(l))) return "NONE";
    if (!is_palin(a.substr(0, l))) return "NONE";
    for (int i = 2; i < l; ++i) {
        if (is_palin(a.substr(0, i))) return "NONE";
    }
    return a + " | " + char(now - 1) + " | " + char('0' + (l+1)/2);
}

int main() {
    int n = 6;
    for (int l = 2; l <= n; ++l) {
        cout << n << ' ' << l << ' ' << simul(n, l) << endl;
    }
    //return 0;

    cin >> n >> k;
    p[0] = 1;
    for (int i = 1; i <= n; ++i) {
        p[i] = mul(p[i - 1], k);
    }

    f[1] = f[2] = k;
    for (int i = 3; i <= n; ++i) {
        f[i] = p[(i + 1) / 2];
        for (int j = 2; j <= (i + 1) / 2; ++j) {
            f[i] = sub(f[i], mul(f[j], p[(i - j * 2 + 1) / 2]));
        }
        cerr << "f " << i << ' ' << f[i] << endl;
    }

    int res = 0;
    for (int i = 1; i <= n; ++i) {
        cerr << "res " << i << ' ' << get_res(i) << endl;
        res = add(res, get_res(i));
    }
    cout << res << endl;
}