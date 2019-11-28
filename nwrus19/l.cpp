#include <bits/stdc++.h>

using namespace std;

const int N = 200010;
const int LOG = 20;

char s[N];
pair<int, int> minVal[LOG][N];
int lg2[N];

struct Fraction {
    int x, y;

    bool operator < (const Fraction &u) const {
        return 1ll * x * u.y < 1ll * u.x * y;
    }
    void normalize() {
        int z = __gcd(x, y);
        x /= z;
        y /= z;
    }
} res;

pair<int, int> rmq(int l, int r) {
    int lg = lg2[r - l + 1];
    return min(minVal[lg][l], minVal[lg][r - (1 << lg) + 1]);
}

struct SA {
    int n;
    char *s;
    int sa[N], tmp[N], pos[N];
    int cnt, lcp[N];
    int minVal[LOG][N];

    void init(char *t) {
        s = t;
        n = strlen(s + 1);
        buildSA();
    }

    void buildSA() {
        for (int i = 1; i <= n; i++) {
            pos[i] = s[i];
            sa[i] = i;
        }
        int len = 1;

        auto cmp = [&](int u, int v) {
            if (pos[u] != pos[v]) return pos[u] < pos[v];
            return (u + len <= n && v + len <= n) ? pos[u + len] < pos[v + len] : u > v;
        };
        while (len < n) {
            sort(sa + 1, sa + n + 1, cmp);
            tmp[1] = 1;
            for (int i = 2; i <= n; i++) {
                tmp[i] = tmp[i - 1] + cmp(sa[i - 1], sa[i]);
            }
            for (int i = 1; i <= n; i++) {
                pos[sa[i]] = tmp[i];
            }
            len <<= 1;
        }
//        for (int i = 1; i <= n; i++) {
//            for (int j = sa[i]; j <= n; j++) cout << s[j];
//            cout << endl;
//        }
        len = 0;
        for (int i = 1; i <= n; i++) {
            if (pos[i] == n) continue;
            int j = sa[pos[i] + 1];
            while (s[i + len] == s[j + len]) len++;
            lcp[pos[i]] = len;
            if (len) len--;
        }
    }
} sa;

void join(set<int> &u, set<int> &v, int len) {
    if (u.size() < v.size()) u.swap(v);
    for (int val : v) {
        auto it = u.lower_bound(val);
        if (it != u.end()) {
            if (len) res = max(res, {len + abs(*it - val), abs(*it - val)});
        }
        if (it != u.begin()) {
            it--;
            if (len) res = max(res, {len + abs(*it - val), abs(*it - val)});
        }
    }
    for (int val : v) u.insert(val);
}

set<int> solve(int l, int r) {
    if (l == r) {
        set<int> s;
        s.insert(sa.sa[l]);
//        cout << "in " << l << ' ' << r << endl;
//        for (int u : s) cout << u << ' ';
//        cout << endl;
        return s;
    }
    pair<int, int> pos = rmq(l, r - 1);
    set<int> ll = solve(l, pos.second);
    set<int> rr = solve(pos.second + 1, r);
    join(ll, rr, pos.first);
//    cout << "in " << l << ' ' << r << ' ' << pos.second << endl;
//    for (int u : ll) cout << u << ' ';
//    cout << endl;
    return ll;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    lg2[1] = 0;
    for (int i = 2; i < N; i++) lg2[i] = lg2[i >> 1] + 1;

    cin >> (s + 1);
    int n = strlen(s + 1);
    sa.init(s);
    for (int i = 1; i < n; i++) {
        minVal[0][i] = {sa.lcp[i], i};
    }
    for (int i = 1; i < LOG; i++) {
        for (int j = 1; j + (1 << i) - 1 < n; j++) {
            minVal[i][j] = min(minVal[i - 1][j], minVal[i - 1][j + (1 << i - 1)]);
        }
    }
    res = {1, 1};
    solve(1, n);
    res.normalize();
    cout << res.x << '/' << res.y << endl;
    return 0;
}