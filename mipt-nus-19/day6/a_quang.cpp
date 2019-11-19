#include <bits/stdc++.h>

using namespace std;

const int N = 50010;
const int LOG = 35;
const int MOD = (int)1e9 + 7;
const int INF = (int)1e9 + 10;

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

struct Rect {
    int x, y, xx, yy;

    int getArea() {
        return 1ll * (xx - x + 1) * (yy - y + 1) % MOD;
    }
} a[N];

int n;
int delta[N];

struct IT {
    int n;
    int sum[N << 3], delta[N << 3];
    int val[N << 1];

    void init(int node, int l, int r) {
        sum[node] = delta[node] = 0;
        if (l < r) {
            int m = l + r >> 1;
            init(node << 1, l, m);
            init(node << 1 | 1, m + 1, r);
        }
    }

    void init(const vector<int> &vals) {
        for (int i = 0; i < vals.size(); i++) {
            val[i] = vals[i];
        }
        n = vals.size() - 1;
        init(1, 1, n);
    }

    int getVal(int l, int r) {
        return (val[r] - val[l - 1]) % MOD;
    }

    void pull(int node, int l, int r) {
        sum[node] = add(sum[node << 1], sum[node << 1 | 1]);
        sum[node] = add(sum[node], mul(delta[node], getVal(l, r)));
    }

    void update(int node, int l, int r, int x, int y, int val) {
        if (x > r || y < l) return;
        if (x <= l && r <= y) {
            sum[node] = add(sum[node], mul(val, getVal(l, r)));
            delta[node] = add(delta[node], val);
            return;
        }
        int m = l + r >> 1;
        update(node << 1, l, m, x, y, val);
        update(node << 1 | 1, m + 1, r, x, y, val);
        pull(node, l, r);
    }

    int get(int node, int l, int r, int x, int y) {
        if (x > r || y < l) return 0;
        if (x <= l && r <= y) return sum[node];
        int m = l + r >> 1;
        int res = 0;
        res = add(res, get(node << 1, l, m, x, y));
        res = add(res, get(node << 1 | 1, m + 1, r, x, y));
        int ll = max(l, x);
        int rr = min(r, y);
        if (ll <= rr) {
            res = add(res, mul(delta[node], getVal(ll, rr)));
        }
        return res;
    }
} unitIT, timeIT;

struct Event {
    int t, l, r, val, type, isUnit;
    bool operator < (const Event &u) const {
        if (t != u.t) return t < u.t;
        if (type != u.type) return type == 0;
        return 0;
    }
};

void solve(int l, int r) {
    if (l == r) return;
    int m = l + r >> 1;
    solve(l, m);

    //update contribution
    vector<Event> events;
    vector<int> vals;

    for (int i = l; i <= m; i++) {
        events.push_back({a[i].x, a[i].y, a[i].yy, mul(delta[i], sub(1, a[i].x % MOD)), 0, 1});
        events.push_back({a[i].xx + 1, a[i].y, a[i].yy, mul(delta[i], a[i].xx % MOD), 0, 1});
        events.push_back({a[i].x, a[i].y, a[i].yy, delta[i], 0, 0});
        events.push_back({a[i].xx + 1, a[i].y, a[i].yy, sub(0, delta[i]), 0, 0});
        vals.push_back(a[i].y - 1);
        vals.push_back(a[i].yy);
    }

    for (int i = m + 1; i <= r; i++) {
        events.push_back({a[i].x - 1, a[i].y, a[i].yy, i, -1, 0});
        events.push_back({a[i].xx, a[i].y, a[i].yy, i, 1, 0});
        vals.push_back(a[i].y - 1);
        vals.push_back(a[i].yy);
    }

    vals.push_back(0);
    sort(vals.begin(), vals.end());
    vals.resize(unique(vals.begin(), vals.end()) - vals.begin());

    unitIT.init(vals);
    timeIT.init(vals);

    sort(events.begin(), events.end());
    for (Event event : events) {
        int l = lower_bound(vals.begin(), vals.end(), event.l - 1) - vals.begin();
        int r = lower_bound(vals.begin(), vals.end(), event.r) - vals.begin();
        if (event.type == 0) { // update
            if (event.isUnit) unitIT.update(1, 1, unitIT.n, l + 1, r, event.val);
            else timeIT.update(1, 1, timeIT.n, l + 1, r, event.val);
        } else { // query   
            int foo = unitIT.get(1, 1, unitIT.n, l + 1, r);
            int bar = timeIT.get(1, 1, timeIT.n, l + 1, r);
            foo = add(foo, mul(bar, event.t % MOD));
            if (event.type == 1) delta[event.val] = add(delta[event.val], foo);
            else delta[event.val] = sub(delta[event.val], foo); 
        }
    }  
    solve(m + 1, r);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y >> a[i].xx >> a[i].yy;
        a[i].y += INF;
        a[i].yy += INF;
        a[i].x += INF;
        a[i].xx += INF;
    }
    for (int i = 1; i <= n; i++) {
        delta[i] = a[i].getArea();
    }
    solve(1, n);
    int res = 0;
    for (int i = 1; i <= n; i++) {
        res = add(res, mul(delta[i], a[i].getArea()));
    }
    cout << res << endl;
    return 0;
}