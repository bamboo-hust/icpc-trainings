#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int MOD = 1e9 + 7;

vector<int> a[N];
int n;

long long f[N][3];

long long inverse(long long a) {
    int p = MOD - 2;
    long long res = 1;
    while (p > 0) {
        if (p & 1) {
            res = res * a % MOD;
        }
        p >>= 1;
        a = a * a % MOD;
    }
    return res;
}

void dfs_init(int u, int p) {
    if (p != 0) a[u].erase(find(begin(a[u]), end(a[u]), p));
    for (int v : a[u]) {
        dfs_init(v, u);
    }
}

void dfs_dp(int u) {
    for (int v : a[u]) dfs_dp(v);
    long long c1 = 0;
    long long c2 = 0;
    long long c3 = 0;
    long long c4 = 0;

    vector<long long> pre0(a[u].size(), 1);
    vector<long long> suf0(a[u].size() + 1, 1);
    vector<long long> pre1(a[u].size(), 1);
    vector<long long> suf1(a[u].size() + 1, 1);

    if (a[u].size() > 0) pre0[0] = f[a[u][0]][0];
    if (a[u].size() > 0) pre1[0] = f[a[u][0]][1];

    for (int i = 1; i < a[u].size(); ++i) {
        pre0[i] = pre0[i - 1] * f[a[u][i]][0] % MOD;
        pre1[i] = pre1[i - 1] * f[a[u][i]][1] % MOD;
    }

    for (int i = (int)a[u].size() - 1; i >= 0; --i) {
        suf0[i] = suf0[i + 1] * f[a[u][i]][0] % MOD;
        suf1[i] = suf1[i + 1] * f[a[u][i]][1] % MOD;
    }

    for (int i = 0; i < a[u].size(); ++i) {
        int v = a[u][i];
        c1 = (c1 + f[v][2] * (i ? pre1[i - 1] : 1) % MOD * suf1[i + 1] % MOD) % MOD;
    }

    c2 = pre1.size() ? pre1.back() : 1;

    for (int i = 0; i < a[u].size(); ++i) {
        assert(i + 1 < suf0.size());

        int v = a[u][i];
        c3 = (c3 + f[v][2] * (i ? pre0[i - 1] : 1) % MOD * suf0[i + 1] % MOD) % MOD;
    }

    long long pre = 0;
    for (int i = 0; i < a[u].size(); ++i) {
        int v = a[u][i];
        c4 = (c4 + f[v][2] * suf0[i + 1] % MOD * pre % MOD) % MOD;
        pre = pre * f[v][0] % MOD;
        pre = (pre + f[v][2] * (i ? pre0[i - 1] : 1) % MOD) % MOD;
    }

    f[u][0] = (c1 + c4 + c2) % MOD;
    f[u][1] = c4;
    f[u][2] = (c2 + c3) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    dfs_init(1, 0);
    dfs_dp(1);
    cout << f[1][0] << endl;
}
