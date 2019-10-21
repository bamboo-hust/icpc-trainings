#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;
const int MOD = 1e9 + 7;

int a[N];
pair<int, int> b[N];
int n;

pair<int, int> merge(pair<int, int> a, pair<int, int> b) {
    if (a.first < b.first) swap(a, b);
    if (a.first == b.first) {
        a.second += b.second;
        if (a.second >= MOD) a.second -= MOD;
    }
    return a;
}

pair<int, int> get(int x) {
    pair<int, int> res = make_pair(0, 0);
    for (++x; x; x -= x & -x) {
        res = merge(res, b[x]);
    }
    return res;
}

void update(int x, pair<int, int> v) {
    for (++x; x <= n; x += x & -x) {
        b[x] = merge(b[x], v);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        vector<int> V(a + 1, a + 1 + n);
        sort(V.begin(), V.end());
        for (int i = 1; i <= n; ++i) {
            a[i] = lower_bound(V.begin(), V.end(), a[i]) - V.begin() + 1;
        }

        for (int i = 0; i <= n + 1; ++i) b[i] = make_pair(0, 0);
        pair<int, int> res = make_pair(0, 1);
        update(0, make_pair(0, 1));

        for (int i = 1; i <= n; ++i) {
            pair<int, int> cur = get(a[i] - 1);
            cur.first++;
            update(a[i], cur);
            res = merge(res, cur);
            //cerr << i << ' ' << cur.first << ' ' << cur.second << endl;
        }

        cout << res.second << '\n';
    }
}