#include <bits/stdc++.h>

using namespace std;

const int N = 200010;
const int SZ = 7;
const int MOD[SZ] = {1000000007, 1000000003, 1000000009, rand() % (int)1e9 + (int)1e4, rand() % (int)1e9 + (int)1e4, rand() % (int)1e9 + (int)1e4, rand() % (int)1e9 + (int)1e4};
const int BASE = 1000007;

inline int add(int u, int v, int MOD) {
    return (u += v) >= MOD ? u - MOD : u;
}

inline int sub(int u, int v, int MOD) {
    return (u -= v) < 0 ? u + MOD : u;
}

inline int mul(int u, int v, int MOD) {
    return (long long)u * v % MOD;
}

struct Hash {
    int h[SZ];
    Hash(int u = 0) {
        for (int i = 0; i < SZ; i++) h[i] = u;
    }
    Hash operator + (const Hash &u) const {
        Hash res;
        for (int i = 0; i < SZ; i++) res.h[i] = add(h[i], u.h[i], MOD[i]);
        return res;
    }
    Hash operator - (const Hash &u) const {
        Hash res;
        for (int i = 0; i < SZ; i++) res.h[i] = sub(h[i], u.h[i], MOD[i]);
        return res;
    }
    Hash operator * (const Hash &u) const {
        Hash res;
        for (int i = 0; i < SZ; i++) res.h[i] = mul(h[i], u.h[i], MOD[i]);
        return res;
    }
    bool operator < (const Hash &u) const {
        for (int i = 0; i < SZ; i++) {
            if (h[i] != u.h[i]) return h[i] < u.h[i];
        }
        return 0;
    }
};

int n;

int a[N];
Hash pre[N], suf[N];
Hash b, powB[N];

pair<Hash, Hash> getHash(int l, int r) {
    Hash foo = pre[r] - (pre[l - 1] * powB[r - l + 1]);
    Hash bar = suf[l] - (suf[r + 1] * powB[r - l + 1]);
    if (foo < bar) swap(foo, bar);
    return {bar, foo};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    b = Hash(BASE);
    powB[0] = Hash(1);
    for (int i = 1; i <= n; i++) powB[i] = powB[i - 1] * b;
    pre[0] = 0;
    for (int i = 1; i <= n; i++) {
        pre[i] = (pre[i - 1] * b) + a[i];
    }
    suf[n + 1] = 0;
    for (int i = n; i; i--) {
        suf[i] = (suf[i + 1] * b) + a[i];
    }
    int maxDiff = 0;
    vector<int> res;
    for (int i = 1; i <= n; i++) {
        set<pair<Hash, Hash>> s;
        for (int j = i; j <= n; j += i) {
            pair<Hash, Hash> now = getHash(j - i + 1, j);
            s.insert(now);
        }
        if (maxDiff == s.size()) res.push_back(i);
        else if (maxDiff < s.size()){
            maxDiff = s.size();
            res.clear();
            res.push_back(i);
        }
    }
    cout << maxDiff << ' ' << res.size() << '\n';
    for (int u : res) cout << u << ' ';
    cout << '\n';
    return 0;
}